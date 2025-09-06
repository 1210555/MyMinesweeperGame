#include "Game.hpp" 
#include <iostream>
#include <cstdlib> 

Game::Game()
    :  UI_AREA_HEIGHT(140),//UI部分の高さ
       numCol(5),
       numRow(5),
       numMine(5),
       font(),             // sf::Font をデフォルト構築 (ロードは後で行う)
       window(sf::VideoMode(1600+UI_AREA_HEIGHT, 800), "MineSweeper",sf::Style::Titlebar | sf::Style::Close),
       state(GameState::MainMenu), //ゲーム初期設定
       level(LevelState::BeforeChoosing),//難易度初期設定
       openNumber(0),
       initialTotalPlace(numCol * numRow),
       initialSafePlace(initialTotalPlace - numMine),
       firstClick(true),
       ignoreOneFrameClick(false),
       field(numCol,numRow,numMine),
       gameRenderer(UI_AREA_HEIGHT),
       gameUI(1600+UI_AREA_HEIGHT,800, UI_AREA_HEIGHT)
{
    if(!font.loadFromFile("resources/arial.ttf")){
        std::cerr << "Error loading font: resources/arial.ttf" << std::endl;
        window.close();
        exit(EXIT_FAILURE); // フォントロード失敗時は終了
    }
    // ロードしたフォントを GameUI に設定
    gameUI.setFont(font);
    gameUI.updateLayout(1600+UI_AREA_HEIGHT,800);
}

// ゲームの状態をリセットする関数
void Game::resetGame(){
    field = Field(numCol,numRow,numMine); //Fieldオブジェクトを再構築しリセット
    openNumber = 0; //OpenNumberリセット
    state = GameState::Playing; //状態をPlayingに戻す
    firstClick=true;
    gameUI.startGameTimer();//時間をupdateLayout関数内で初期化し、0に
}
void Game::gameLevel(LevelState choosenLevel){
    if(choosenLevel==LevelState::Easy){
        numCol=5;
        numRow=10;
        numMine=5;
    }else if(choosenLevel==LevelState::Normal){
        numCol=10;
        numRow=20;
        numMine=30;
    }else if(choosenLevel==LevelState::Hard){
        numCol=16;
        numRow=32;
        numMine=60;
    }
    initialTotalPlace=numCol*numRow;
    initialSafePlace=initialTotalPlace - numMine;
    window.create(sf::VideoMode(numRow*50,numCol*50+UI_AREA_HEIGHT),"MineSweeper",sf::Style::Titlebar | sf::Style::Close);
    field=Field(numCol,numRow,numMine);
    gameUI.updateLayout(window.getSize().x,window.getSize().y);
}

void Game::Run(){
    int tileSize = 50; //タイルサイズ(ゲーム全体で共通の定数)
    sf::Event event;
    while(window.isOpen()){
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }

            // マウスのクリック座標の取得とUI部分の調整
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            int x = mousePos.x / tileSize;
            int y = (mousePos.y - UI_AREA_HEIGHT) / tileSize;
            

           // 左クリックの処理
            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                if(state==GameState::MainMenu){
                    if(gameUI.isEasyButtonClicked(mousePos)){
                        level=LevelState::Easy;
                        resetGame();
                        gameLevel(level);
                        firstClick=true;;
                    }else if(gameUI.isNormalButtonClicked(mousePos)){
                        level=LevelState::Normal;
                        resetGame();
                        gameLevel(level);
                        firstClick=true;
                        ignoreOneFrameClick=true;
                    }else if(gameUI.isHardButtonClicked(mousePos)){
                        level=LevelState::Hard;
                        resetGame();
                        gameLevel(level);
                        firstClick=true;
                        ignoreOneFrameClick=true;
                    }
                }
                   
                // UI エリアのクリックの処理
                if(mousePos.y >= 0 && mousePos.y < UI_AREA_HEIGHT){
                    if(state == GameState::GameOver || state == GameState::Win){
                        if  (gameUI.isGoTitleButtonClicked(mousePos)){
                            state=GameState::MainMenu;
                            window.create(sf::VideoMode(32 * 50, 16 * 50 + UI_AREA_HEIGHT), "MineSweeper",sf::Style::Titlebar | sf::Style::Close);//mainmenuは常に1600×870
                            gameUI.updateLayout(32 * 50, 16 * 50 + UI_AREA_HEIGHT);
                            level=LevelState::BeforeChoosing;
                        }
                    }else if(state==GameState::Playing){
                        if(gameUI.isMenuButtonClicked(mousePos)){
                            state=GameState::PauseMenu;
                            gameUI.pauseTimer();
                        }
                    }
                }else if(state==GameState::PauseMenu){
                    if(gameUI.isContinueButtonClicked(mousePos)){
                        gameUI.startGameTimer();
                        state=GameState::Playing;
                    }else if(gameUI.isFinishButtonClicked(mousePos)){
                        window.create(sf::VideoMode(32 * 50, 16 * 50 + UI_AREA_HEIGHT), "MineSweeper",sf::Style::Titlebar | sf::Style::Close);//mainmenuは常に1600×870
                        gameUI.updateLayout(32 * 50, 16 * 50 + UI_AREA_HEIGHT);
                        state=GameState::MainMenu;
                        level=LevelState::BeforeChoosing;
                    }
                    //プレイ中のロジック
                }else if(state == GameState::Playing){
                    // クリック座標が有効な範囲内かチェック
                    if (x >= 0 && x < numRow && y >= 0 && y < numCol){
                        //ignoreOneFrameClickのif以下をスキップし難易度決定時のクリックをfirstClickに見なされないようにする
                        //これないと難易度選択のクリックがマスの開放に見なされてしまう
                        if(ignoreOneFrameClick){
                            ignoreOneFrameClick=false;
                            continue;
                        }
                        if(firstClick){
                            field.minePlace(y,x);
                            firstClick=false;
                        }
                        if (field.Flagged(y, x)) {
                            continue;
                        } else if (field.Opened(y, x)) {
                            continue;
                        } else if (field.Mined(y, x)) {
                            state = GameState::GameOver;
                        } else {
                            openNumber += field.autoRelease(y, x); 
                            if (openNumber == initialSafePlace) {
                                state = GameState::Win;
                            }
                        }
                    }
                }
            }
            // 右クリック
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
                if (state == GameState::Playing) {
                    if (x >= 0 && x < numRow && y >= 0 && y < numCol) {
                        if (!field.Opened(y, x)) {
                            field.Flag(y, x); //フラグをトグル
                        }
                    }
                }
            }
        }
        window.clear(sf::Color::Black);//デフォルトの色
        
        if(state==GameState::Playing||state==GameState::GameOver||state==GameState::Win||state==GameState::MainMenu){
            gameRenderer.display(window, tileSize, state, font, field, field.getOpen(), field.getFlag(),numCol,numRow,numMine);
        }
        gameUI.updateTimer(state);
        gameUI.Draw(window, state);
        window.display();
    }
}