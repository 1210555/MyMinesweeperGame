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
    frag (numRow,std::vector<bool>(numCol, false)),
    fieldOfNumCol(numCol),
    fieldOfNumRow(numRow),
    fieldOfNumMine(numMine)
    {}


void Field::minePlace(int avoidRow,int avoidCol){
    int placed = 0;
    while(placed < fieldOfNumMine){
        int mineRow = rand() % fieldOfNumRow;
        int mineCol = rand() % fieldOfNumCol;
        if(mine[mineRow][mineCol]){
            continue;
        }
        if(abs(mineRow-avoidRow)<=1&&abs(mineCol-avoidCol)<=1){
            continue;
        }
        mine[mineRow][mineCol] = true;
        placed++;
    }
}

int Field::Count(int x, int y)const{
    int AroundMineCount = 0;
    int dx[8]={-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[8]={-1, 0, 1, -1, 1, -1, 0, 1};

    for (int k = 0; k < 8; k++){
        int nx = x + dx[k];
        int ny = y + dy[k];
        if (nx >= 0 && nx < fieldOfNumRow && ny >= 0 && ny < fieldOfNumCol){
            if (mine[nx][ny]){
                AroundMineCount++;
            }
        }
    }
    return AroundMineCount;
}

bool Field::Mined(int x,int y)const{
    return mine[x][y];
}

void Field::Open(int x,int y){
    open[x][y]=true;
}

bool Field::Opened(int x,int y)const{
    return open[x][y];
}

const std::vector<std::vector<bool>>& Field::getOpen()const{
    return open;
}

void Field::Flag(int x,int y){
    frag[x][y] = !frag[x][y];
}

bool Field::Flagged(int x,int y)const{
    return frag[x][y];
}

const std::vector<std::vector<bool>>& Field::getFlag()const{
    return frag;
}

int Field::autoRelease(int x,int y){
    int OpenCount = 1;
    if (x < 0 || x >= fieldOfNumRow || y < 0 || y >= fieldOfNumCol){
        return 0;
    }
    if (Opened(x, y) || Flagged(x, y)){
        return 0;
    }
    Open(x, y);
    if (Mined(x, y)){
        return 0;
    }
    if (Count(x, y) != 0){
        return OpenCount;
    }

    int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int k = 0; k < 8; k++){
        int nx = x + dx[k];
        int ny = y + dy[k];
        if (nx >= 0 && nx < fieldOfNumRow && ny >= 0 && ny < fieldOfNumCol){
            if (!Opened(nx, ny) && !Flagged(nx, ny)){ // オートリリース中にフラグ付きは開かない
                OpenCount += autoRelease(nx, ny);
            }
        }
    }
    return OpenCount;
}

