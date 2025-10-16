#ifndef FIELD_HPP 
#define FIELD_HPP
#include <vector>
#include <cmath>
#include <functional>
#include "Constants.hpp"

class Field {
private:
    std::vector<std::vector<bool>> mine;
    std::vector<std::vector<bool>> open;
    std::vector<std::vector<bool>> flag;
    int fieldOfNumCol;
    int fieldOfNumRow;
    int fieldOfNumMine;
    //周囲のマスを調べるツールをprivateにする
    //実際に使う周囲の地雷数、フラッグ数をカウントする関数はpublicで実装
    void aroundCellCheck(int row,int col,std::function<void(int,int)> func) const;

public:
    Field(); 
    Field(int numCol,int numRow,int numMine);
    void generateMinesSafe(int avoidRow,int avoidCol); // 周囲の地雷数が０の盤面になるまで再配置し続ける
    bool isAllSafeCellsOpened();
    int getCount(int x, int y) const; // 地雷数カウント
    bool Mined(int x, int y) const; // 地雷判定 
    void Open(int x, int y); // マスを開く
    bool Opened(int x, int y) const; // マスが開かれているか
    const std::vector<std::vector<bool>>& getOpen() const;
    int countUnopened(int x,int y);
    void Flag(int x, int y); // フラグをトグルする
    bool Flagged(int x, int y) const; // フラグが立っているか
    const std::vector<std::vector<bool>>& getFlag() const; 
    int autoRelease(int x, int y); // オートリリース
    int flagCount(int x,int y);//ソルバーで周囲のフラッグ数をカウントする用
    int getNumRow();
    int getNumCol();
    //有効な盤面かどうかのチェック
    void validCell();
    //周囲のフラッグ数チェックの関数
    int openAroundSafeCells(int x,int y);
    //周囲の未開放マスの個数チェックの関数
    int flagsAroundCells(int x,int y);
};

#endif 