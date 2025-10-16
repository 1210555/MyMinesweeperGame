#pragma once
#include "Field.hpp"
#include "GameUI.hpp"
#include <SFML/System/Vector2.hpp>

// ヒントの種類と座標を保持するための構造体
struct Hint{
    enum HintType{ 
        None, // ヒントが見つからなかった
        Safe // 安全なマス
    };
    HintType type=None;//初期値はNone
    sf::Vector2i pos;
};

class Solver{
public:
    // コンストラクタ: どの盤面を解くか、Fieldオブジェクトへの参照を受け取る
    Solver(Field& field);

    // ソルバーのメイン関数: 盤面が解けるかどうかを判定する
    bool isSolvable();

    Hint findHint();

private:
    // ソルバーが操作する盤面への参照
    Field& m_field; 

    // ソルバーの基本的な手筋を実装する関数
    int revealKnownSafeCells(); // 数字と旗の数が一致したら周りを開く
    int flagKnownMineCells();   // 数字と未開封マスの数が一致したら旗を立てる

    //安全なマスを探すヒント用の関数
    Hint findNextSafeCell();
};