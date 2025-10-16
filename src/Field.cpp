#include "Field.hpp" 
#include <cstdlib> 
#include <ctime>
#include <cmath> 

Field::Field()
:Field(5,5,3)//仮の値で初期化
{}

Field::Field(int numRow,int numCol,int numMine)//難易度に応じたフィールドサイズ、地雷数
  : mine (numRow,std::vector<bool>(numCol, false)),
    open (numRow,std::vector<bool>(numCol, false)),
    flag (numRow,std::vector<bool>(numCol, false)),
    fieldOfNumCol(numCol),
    fieldOfNumRow(numRow),
    fieldOfNumMine(numMine)
    {}

void Field::aroundCellCheck(int row,int col,std::function<void(int ,int)> func)const{
    for(int i=-1; i<=1;i++){
        for(int j=-1; j<=1; j++){
            if(i ==0 && j == 0) continue;
            int aroundX=row+i;
            int aroundY=col+j;
        //有効なマスか
            if (aroundX<0 || aroundX>=fieldOfNumRow || aroundY<0 || aroundY>=fieldOfNumCol) continue;
            func(aroundX,aroundY);
        }
    }
}

int Field::openAroundSafeCells(int x,int y){
    int revealedCount=0;

    aroundCellCheck(x,y,[&](int nx,int ny){
        if(!Opened(nx,ny) && !Flagged(nx,ny)){
            revealedCount+=autoRelease(nx,ny);
        }
    });
    return revealedCount;
}

//未開放かつフラッグのないますにフラッグを立てる
//立てたフラッグの数を返す
int Field::flagsAroundCells(int x,int y){
    int flaggedCount = 0;

    aroundCellCheck(x,y,[&](int nx,int ny){
        if (!Opened(nx,ny) && !Flagged(nx,ny)) {
            Flag(nx,ny);
            flaggedCount++;
        }
    });
    return flaggedCount;
}

//クリックした座標を受け取りその周辺の地雷数が０になるまで盤面生成
void Field::generateMinesSafe(int avoidRow,int avoidCol){
    int placed=0;//設置した地雷の数
    //設置数が指定された地雷数と同じになれば設置完了
    while(placed < fieldOfNumMine){
        int mineRow = rand() % fieldOfNumRow;
        int mineCol = rand() % fieldOfNumCol;

        //すでにマスに地雷設置済みの処理
        if(mine[mineRow][mineCol]){
            continue;
        }
        //設置したい場所(mineRow,mineCol)の周囲にクリックした座標(avoidRow,avoidCol)があるか
        //地雷を設置したい場所とクリックした座標の絶対値をとることで条件分岐
        if(abs(mineRow-avoidRow)<=1&&abs(mineCol-avoidCol)<=1){
            continue;
        }
        mine[mineRow][mineCol] = true;
        placed++;
    }
}

//安全なすべてのマスが開かれているかのチェック
bool Field::isAllSafeCellsOpened(){
    for(int row=0;row<fieldOfNumRow;row++){
        for(int col=0;col<fieldOfNumCol;col++){
            //地雷でなく、未開放のマスあればfalse
            if(!Mined(row,col)&&!Opened(row,col)){
                return false;
            }
        }
    }
    //すべての安全なマスの開放が行えた時ture
    return true;
}

//地雷の周囲のフラッグマスをカウント
int Field::flagCount(int x,int y){
    int aroundFlagCount=0;//周囲のフラッグ数
    int dx[8]={-1, -1, -1, 0, 0, 1, 1, 1};//
    int dy[8]={-1, 0, 1, -1, 1, -1, 0, 1};

    //地雷の周囲８マスをチェック
    for (int k=0;k<8;k++){
        int aroundX=x+dx[k];//クリックしたマスの周囲のマスのｘ座標
        int aroundY=y+dy[k];//クリックしたマスの周囲のマスのｙ座標
        //盤面の範囲内にあるかのチェック(はしっこのマスは周囲のマスがないこともあるため)
        if (aroundX>=0 && aroundX<fieldOfNumRow && aroundY>=0 && aroundY<fieldOfNumCol){
            if (flag[aroundX][aroundY]){
                aroundFlagCount++;
            }
        }
    }
    return aroundFlagCount;
}

//行数を渡す（今んとこSolverに）
int Field::getNumRow(){
    return fieldOfNumRow;
}

//列数を渡す（今んとこSolverに）
int Field::getNumCol(){
    return fieldOfNumCol;
}

//クリックした座標(x,y)
int Field::getCount(int x, int y)const{
    int AroundMineCount = 0;
    int dx[8]={-1,-1,-1,0,0,1,1,1};//地雷数チェックの行の値
    int dy[8]={-1,0,1,-1,1,-1,0,1};//地雷数チェックの列の値

    for (int k=0;k<8;k++){
        int aroundX=x+dx[k];
        int aroundY=y+dy[k];
        if (aroundX >= 0 && aroundX < fieldOfNumRow && aroundY >= 0 && aroundY < fieldOfNumCol){
            if (mine[aroundX][aroundY]){
                AroundMineCount++;
            }
        }
    }
    return AroundMineCount;
}

//座標(x,y)に地雷があるかどうかを返す
bool Field::Mined(int x,int y)const{
    return mine[x][y];
}

//座標(x,y)を実際にあける
void Field::Open(int x,int y){
    open[x][y]=true;
}

//座標(x,y)が開いているかどうかを返す
bool Field::Opened(int x,int y)const{
    return open[x][y];
}

//開いているマスがtrueの配列
const std::vector<std::vector<bool>>& Field::getOpen()const{
    return open;
}

//座標(x,y)のマスの周囲に未開放のマスが何個あるか(Solverで使用)
int Field::countUnopened(int x,int y){
    int unopenedCount=0;//未開放マスの個数
    for(int i=-1;i<=1;i++){
        for(int j=-1;j<=1;j++){
            int aroundX=x+i;
            int aroundY=y+j;
//例１
            //有効な盤面かどうかを判断
            if (aroundX<0 || aroundX>=fieldOfNumRow || aroundY<0 || aroundY>=fieldOfNumCol) continue;
            if(!Opened(aroundX,aroundY)){
                unopenedCount++;
            }
//例２
            // //有効な盤面内かどうかのチェック
            // if(aroundX>=0 && aroundX<fieldOfNumRow && aroundY>=0 && aroundY<fieldOfNumCol){
            //     //周囲に開いていないマスがあればunopenedCount進める
            //     if(!Opened(aroundX,aroundY)){
            //         unopenedCount++;
            //     }
            // }
        }
    }
    return unopenedCount;
}

//座標(x,y)のフラッグをトグル
void Field::Flag(int x,int y){
    flag[x][y] = !flag[x][y];
}

//座標(x,y)にフラッグがあるか返す
bool Field::Flagged(int x,int y)const{
    return flag[x][y];
}

//フラッグの立ってるマスがtrueの配列
const std::vector<std::vector<bool>>& Field::getFlag()const{
    return flag;
}

int Field::autoRelease(int x,int y){
    int OpenCount=1;
    if(x<0 || x>=fieldOfNumRow || y<0 || y>=fieldOfNumCol){
        return 0;
    }
    if(Opened(x,y) || Flagged(x,y)){
        return 0;
    }
    Open(x,y);
    if(Mined(x,y)){
        return 0;
    }
    if(getCount(x,y)!=0){
        return OpenCount;
    }

    int dx[8]={-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[8]={-1, 0, 1, -1, 1, -1, 0, 1};

    //地雷の周囲８マスをチェック
    for(int k = 0; k < 8; k++){
        int aroundX=x+dx[k];//クリックしたマスの周囲のマスのｘ座標
        int aroundY=y+dy[k];//クリックしたマスの周囲のマスのｙ座標
        if(aroundX>=0 && aroundX<fieldOfNumRow && aroundY>=0 && aroundY<fieldOfNumCol){
            if(!Opened(aroundX,aroundY) && !Flagged(aroundX,aroundY)){ // オートリリース中にフラグ付きは開かない
                OpenCount += autoRelease(aroundX,aroundY);
            }
        }
    }
    return OpenCount;
}

