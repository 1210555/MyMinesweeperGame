#include "Game.hpp" 
#include <iostream>
#include <cstdlib> 

Game::Game()
    :  UI_AREA_HEIGHT(140),//UI部分の高さ
       numCol(5),
       numRow(5),
       numMine(5),
       font(),// sf::Font をデフォルト構築 (ロードは後で行う)
       myFont(),//
       fieldFont(),//周囲の地雷数表示のフォント
       window(sf::VideoMode(1600+UI_AREA_HEIGHT, 800), "MineSweeper",sf::Style::Titlebar | sf::Style::Close),
       state(GameState::MainMenu), //ゲーム初期設定
       level(LevelState::BeforeChoosing),//難易度初期設定
       openNumber(0),
       initialTotalPlace(numCol * numRow),
       initialSafePlace(initialTotalPlace - numMine),
       firstClick(true),
       field(numCol,numRow,numMine),
       gameRenderer(UI_AREA_HEIGHT),
       gameUI(1600+UI_AREA_HEIGHT,800, UI_AREA_HEIGHT)
{
    if(!font.loadFromFile("assets/Fonts/LibertinusKeyboard-Regular.ttf")){
        std::cerr << "Error loading font: assets/fonts/LibertinusKeyboard-Regular.ttf" << std::endl;
        window.close();
        exit(EXIT_FAILURE); // フォントロード失敗時は終了
    }
    if(!myFont.loadFromFile("assets/Fonts/FrederickatheGreat-Regular.ttf")){
        std::cerr << "Error loading font: assets/fonts/FrederickatheGreat-Regular.ttf" << std::endl;
        window.close();
        exit(EXIT_FAILURE); // フォントロード失敗時は終了
    }
    if(!fieldFont.loadFromFile("assets/Fonts/BitcountPropDouble-VariableFont_CRSV,ELSH,ELXP,slnt,wght.ttf")){
        std::cerr << "Error loading font: assets/fonts/BitcountPropDouble-VariableFont_CRSV,ELSH,ELXP,slnt,wght.ttf" << std::endl;
        window.close();
        exit(EXIT_FAILURE); // フォントロード失敗時は終了
    }
    //サウンドの読み込み
    std::cout<<"Loading Sound."<<std::endl;
    m_soundManager.loadSound("click1", "assets/sounds/releaseClick1.wav");
    m_soundManager.loadSound("click2", "assets/sounds/releaseClick2.wav");
    m_soundManager.loadSound("click3", "assets/sounds/releaseClick3.wav");
    m_soundManager.loadSound("flag", "assets/sounds/flag.wav");
    m_soundManager.loadSound("boom", "assets/sounds/explosion.wav");
    m_soundManager.loadSound("win_sound", "assets/sounds/win_Sound.wav");
    m_soundManager.loadSound("win_voice", "assets/sounds/win_Voice.wav");
    m_soundManager.loadSound("gameOver", "assets/sounds/gameOver.wav");
    m_soundManager.loadSound("autoRelease1", "assets/sounds/autoRelease1.wav");
    m_soundManager.loadSound("autoRelease2", "assets/sounds/autoRelease2.wav");
    m_soundManager.loadSound("chancelFlag", "assets/sounds/chancelFlag.wav");
     /*if (!buffer.loadFromFile(filename)) {
        // エラーメッセージをコンソールに出力
        std::cerr << "Error loading sound file: " << filename << std::endl;
        // このサウンドは読み込めなかったので、処理を中断する
        return; 
    }*/

    // ロードしたフォントを GameUI に設定
    gameUI.setMainFont(myFont);
    gameUI.setFont(font);
    gameUI.initializeStyles();
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
    int tileSize=50; //タイルサイズ(ゲーム全体で共通の定数)
    sf::Event event;
    while(window.isOpen()){
            sf::Vector2i mousePos=sf::Mouse::getPosition(window);
            int x=mousePos.x/tileSize;
            int y=(mousePos.y-UI_AREA_HEIGHT)/tileSize;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }

            // マウスのクリック座標の取得とUI部分の調整
            /*sf::Vector2i mousePos=sf::Mouse::getPosition(window);
            int x=mousePos.x/tileSize;
            int y=(mousePos.y-UI_AREA_HEIGHT)/tileSize;*/

           // 左クリックの処理
            if(event.type==sf::Event::MouseButtonPressed && event.mouseButton.button==sf::Mouse::Left){
                if(state==GameState::MainMenu){
                    if(gameUI.isEasyButtonClicked(mousePos)){
                        level=LevelState::Easy;
                        gameLevel(level);
                        resetGame();
                        firstClick=true;
                    }else if(gameUI.isNormalButtonClicked(mousePos)){
                        level=LevelState::Normal;
                        gameLevel(level);
                        resetGame();
                        firstClick=true;
                    }else if(gameUI.isHardButtonClicked(mousePos)){
                        level=LevelState::Hard;
                        gameLevel(level);
                        resetGame();
                        firstClick=true;
                    }
                }
                else if(state == GameState::GameOver || state == GameState::Win){
                    if  (gameUI.isGoTitleButtonClicked(mousePos)){
                        state=GameState::MainMenu;
                        window.create(sf::VideoMode(32 * 50, 16 * 50 + UI_AREA_HEIGHT), "MineSweeper",sf::Style::Titlebar | sf::Style::Close);//mainmenuは常に1600×870
                        gameUI.updateLayout(32 * 50, 16 * 50 + UI_AREA_HEIGHT);
                        level=LevelState::BeforeChoosing;
                    }
                }
                else if(state==GameState::Playing){
                    //Playing時のみUIエリアかどうかのチェック
                    if(mousePos.y >= 0 && mousePos.y < UI_AREA_HEIGHT){
                        if(gameUI.isMenuButtonClicked(mousePos)){
                            state=GameState::PauseMenu;
                            gameUI.pauseTimer();
                        }
                    }else{
                        if (x >= 0 && x < numRow && y >= 0 && y < numCol){
                            if(firstClick){
                                field.minePlace(y,x);
                                firstClick=false;
                            }
                            if(field.Flagged(y, x)){
                                continue;
                            }else if(field.Opened(y, x)){
                                continue;
                            }else if(field.Mined(y, x)){
                                m_soundManager.playSound("boom");//爆発時のサウンド
                                state = GameState::GameOver;
                            }else{
                                int releaseCount=field.autoRelease(y,x);
                                openNumber+=releaseCount;
                                if(releaseCount==1){
                                    m_soundManager.playSound("click1");//1マス開放時のサウンド
                                }else{
                                    m_soundManager.playSound("autoRelease1");//連鎖的な開放時のサウンド
                                }
                                
                                if (openNumber==initialSafePlace){
                                    m_soundManager.playSound("win_sound");//勝利時のサウンド
                                    m_soundManager.playSound("win_voice");//勝利時のサウンド
                                    state=GameState::Win;
                                }
                            }
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
                }
            }
            // 右クリック
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
                if (state == GameState::Playing) {
                    if (x >= 0 && x < numRow && y >= 0 && y < numCol) {
                        if (!field.Opened(y, x)) {
                            m_soundManager.playSound("flag");//フラグ設置時のサウンド
                            field.Flag(y, x); //フラグをトグル
                        }else{
                            // フラグ解除時のサウンド（別のものにする）
                            m_soundManager.playSound("chancelFlag");
                        }
                    }
                }
            }
        }
        gameUI.updateHoverState(mousePos,state);
        window.clear(sf::Color(10,100,200));//デフォルトの色
        
        if(state==GameState::Playing||state==GameState::GameOver||state==GameState::Win||state==GameState::MainMenu){
            //ここのフォントで周囲の地雷数のフォント変更
            gameRenderer.display(window, tileSize, state, fieldFont, field, field.getOpen(), field.getFlag(),numCol,numRow,numMine);
        }
        gameUI.updateTimer(state);
        gameUI.Draw(window, state);
        window.display();
    }
}