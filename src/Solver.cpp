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

bool Solver::isSolvable(){
    std::cout << "Starting solver..." << std::endl;
    while(true){
        int revealed = revealKnownSafeCells();//解放したマスの数
        int flagged = flagKnownMineCells();//設置したフラッグの数

        std::cout << "Solver step: revealed " << revealed << ", flagged " << flagged << std::endl;

        //解放したマスの数が０かつ設置したフラッグの数が０のとき手詰まり！
        //つまり"詰んでいる状態！"なので盤面生成しなおすためにbreak
        if(revealed==0 && flagged==0){
            break;
        }
    }

    //探索の手が止まったときすべての安全なマスが解放されているか
    if(m_field.isAllSafeCellsOpened()){
        std::cout << "Solver determined: Solvable!" << std::endl;
        return true;
    }else{
        std::cout << "Solver determined: Unsolvable (stuck)." << std::endl;
        return false;
    }
}

//ソルバー用盤面で未開放のマスを開ける
int Solver::revealKnownSafeCells() {
    int totalRevealedCount = 0;

    for(int row=0;row<m_field.getNumRow();row++){
        for(int col=0;col<m_field.getNumCol();col++){
            if(m_field.Opened(row,col) && m_field.getCount(row,col) > 0){

                if(m_field.getCount(row,col) == m_field.flagCount(row,col)){
                    totalRevealedCount+=m_field.openAroundSafeCells(row,col);
                }
            }
        }
    }
    return totalRevealedCount;
}

//ソルバー用盤面で地雷と確定したマスにフラッグを立てる関数
int Solver::flagKnownMineCells(){
    int totalFlaggedCount=0;

    //このループで座標(row,col)のマスの周辺のマスを調べる
    for(int row=0;row<m_field.getNumRow();row++){
        for(int col=0;col<m_field.getNumCol();col++){

        //解放済みかつ周囲の地雷数が0より大きいときフラッグを立てる
            if(m_field.Opened(row,col) && m_field.getCount(row,col) > 0){
                int unopenedCount=m_field.countUnopened(row,col);

            //周囲の地雷数＝周囲の未開放マスとなったとき
                if(m_field.getCount(row,col) == unopenedCount){
                    totalFlaggedCount+=m_field.flagsAroundCells(row,col);
                }
            }
        }
    }
    return totalFlaggedCount;
}

Hint Solver::findNextSafeCell(){
    for(int row=0;row<m_field.getNumRow();row++){
        for(int col=0;col<m_field.getNumCol();col++){
            if(m_field.Opened(row,col) && m_field.getCount(row,col)>0){
                if(m_field.getCount(row,col) == m_field.flagCount(row,col)){
                    // 周囲8マスを調べる
                    for(int i=-1; i<=1; i++){
                        for(int j=-1; j<=1; j++){
                            if (i==0 && j==0) continue;
                            int aroundX=row+i;
                            int aroundY=col+j;

                            if(aroundX<0 || aroundX>=m_field.getNumRow() || aroundY<0 || aroundY>=m_field.getNumCol()) continue;
                            //解放済みもしくはフラッグが立っているマスはcontinue
                            //if(m_field.Opened(aroundX, aroundY) || m_field.Flagged(aroundX, aroundY)) continue;
                            if (!m_field.Opened(aroundX, aroundY) && !m_field.Flagged(aroundX, aroundY)) {
                                // 1つ見つけたら、その座標を返して関数を即終了！
                                return{ Hint::Safe,{aroundX,aroundY}};
                            }
                        }
                    }
                }
            }
        }
    }
    return {Hint::None,{}};
}

Hint Solver::findHint() {
    
    return findNextSafeCell();
}