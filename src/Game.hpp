#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include "Constants.hpp" 
#include "Field.hpp"
#include "GameRenderer.hpp"
#include "GameUI.hpp"
#include "SoundManager.hpp"

class Game{
private:
    const int UI_AREA_HEIGHT;
    sf::Font font;
    sf::RenderWindow window;
    Field field;
    GameState state;//ゲーム状態の管理
    LevelState level;//難易度の状態管理
    GameRenderer gameRenderer;
    GameUI gameUI;
    SoundManager m_soundManager;

    int openNumber;//開かれた安全なマスの数
    int initialOpenNumber;//OpenNumber の初期値 (0)
    int initialTotalPlace;//ボード全体のマス数
    int initialSafePlace;//安全なマスの総数
    bool firstClick;//最初にクリックしたかどうか(これが真となった後に地雷配置)
    //ノーマル、ハード選択時のクリックが反映されるのを防止

public:
    Game();
    void Run();
    void resetGame();
    void gameLevel(LevelState level);
    int numCol;
    int numRow;
    int numMine;
};

#endif