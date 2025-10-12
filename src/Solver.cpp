#include "Solver.hpp"
#include "iostream"

// Solver::Solver(int numRow,int numCol,int numMine){
//     Field field;
// }


// void Solver::fragTuggle(){
//     //この中で全マスのチェックを行う
//     for(int x;x<numRow;x++){
//         for(int y;y<numCol;y++){
//             field.generateSafePlace(int avoidRow,int avoidCol);
//         }
//     }
// }

Solver::Solver(Field& field) : m_field(field) {
    // コンストラクタの初期化子リストで、受け取ったfieldをm_fieldに設定
}

bool Solver::isSolvable() {
    std::cout << "Starting solver..." << std::endl;
    while (true) {
        // 基本的な手筋を順番に試す
        int revealed = revealKnownSafeCells();
        int flagged = flagKnownMineCells();

        std::cout << "Solver step: revealed " << revealed << ", flagged " << flagged << std::endl;

        // もし、このステップで何も進展がなかったら...
        if (revealed == 0 && flagged == 0) {
            break; // 手詰まりなのでループを抜ける
        }
    }

    // ループが終わった後、全ての安全なマスが開かれているかチェック
    // (この isAllSafeCellsOpened() はFieldクラスに新しく作る必要がある)
    if (m_field.isAllSafeCellsOpened()) {
        std::cout << "Solver determined: Solvable!" << std::endl;
        return true;
    } else {
        std::cout << "Solver determined: Unsolvable (stuck)." << std::endl;
        return false;
    }
}

//
int Solver::revealKnownSafeCells() {
    int revealedCount = 0;

    for(int row=0;row<m_field.getNumRow();row++){
        for(int col=0;col<m_field.getNumCol();col++){
            if(m_field.Opened(row,col) && m_field.Count(row,col) > 0){

                if(m_field.Count(row,col) == m_field.flagCount(row,col)){
                    for(int i=-1; i<=1; i++){
                        for(int j=-1; j<=1; j++){
                            //そのマス自身は考慮しない
                            if(i ==0 && j == 0) continue;

                            int aroundX=row+i;
                            int aroundY=col+j;
                            
                        //有効な盤面かどうかを判断
                            if (aroundX<0 || aroundX>=m_field.getNumRow() || aroundY<0 || aroundY>=m_field.getNumCol()) continue;
                            if(!m_field.Opened(aroundX,aroundY) && !m_field.Flagged(aroundX,aroundY)){
                                //m_field.autoRelease(aroundX,aroundY);
                                revealedCount+=m_field.autoRelease(aroundX,aroundY);
                            }
                        }
                    }
                }
            }
        }
    }
    return revealedCount;
}

//地雷と確定したマスにフラッグを立てる関数
//検証したいマスの座標x,yを引数とする
int Solver::flagKnownMineCells(){
    int flaggedCount = 0;

    //このループで座標(row,col)のマスの周辺のマスを調べる
    for(int row=0;row<m_field.getNumRow();row++){
        for(int col=0;col<m_field.getNumCol();col++){
            if(m_field.Opened(row,col) && m_field.Count(row,col) > 0){
                int unopenedCount=m_field.countUnopened(row,col);
                if(m_field.Count(row,col)==unopenedCount){
                    for(int i=-1; i<=1; i++){
                        for(int j=-1; j<=1; j++){
                            int aroundX=row+i;
                            int aroundY=col+j;
                            if(i ==0 && j == 0) continue;
                        //有効な盤面かどうかを判断
                            if (aroundX<0 || aroundX>=m_field.getNumRow() || aroundY<0 || aroundY>=m_field.getNumCol()) continue;
                            if(!m_field.Opened(aroundX,aroundY) && !m_field.Flagged(aroundX,aroundY)){
                                m_field.Flag(aroundX,aroundY);
                                flaggedCount++;
                            }
                        }
                    }
                }
            }
        }
    }
    return flaggedCount;
}