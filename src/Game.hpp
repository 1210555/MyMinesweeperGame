#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include "Constants.hpp" 
#include "Field.hpp"
#include "GameRenderer.hpp"
#include "GameUI.hpp"

class Game {
private:
    const int UI_AREA_HEIGHT; 
    sf::Font font;           
    sf::RenderWindow window; 
    Field field;             
    GameState state;         
    GameRenderer gameRenderer;
    GameUI gameUI;            

    int OpenNumber;// 開かれた安全なマスの数
    int initialOpenNumber;// OpenNumber の初期値 (0)
    int initialTotalPlace;// ボード全体のマス数
    int initialSafePlace;// 安全なマスの総数
    bool firstClick;//最初にクリックしたかどうか(これが真となった後に地雷配置)

public:
    Game();
    void Run();
    void resetGame();

};

#endif