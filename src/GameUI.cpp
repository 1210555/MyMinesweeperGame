#include "GameUI.hpp" // 対応するヘッダーファイルをインクルード
#include <cmath>
#include <iostream>

GameUI::GameUI(int windowWidth, int windowHeight, int offset)
: windowWidth(windowWidth),
  windowHeight(windowHeight),
  uiOffset(offset),
  centerX(windowWidth/2.0f),
  centerY(windowHeight/2.0f)
{
    
}
void GameUI::updateLayout(int newWidth,int newHeight){
    centerX=newWidth/2.0f;//状態に応じて変更した横幅の中間
    centerY=newHeight/2.0f;//状態に応じて変更した縦の長さの中間

//この部分はMainTitle時に移すようにしておく。(Playing時にずっと出さなくてもいい気がする)    
    /*leftInstructionText.setString("Left Click: Open Tile");
    leftInstructionText.setCharacterSize(20);
    leftInstructionText.setFillColor(sf::Color::White);
    leftInstructionText.setPosition(10.0f, 10.0f);

    rightInstructionText.setString("Right Click: Flag Tile");
    rightInstructionText.setCharacterSize(20);
    rightInstructionText.setFillColor(sf::Color::White);
    rightInstructionText.setPosition(10.0f, 40.0f);*/
    endGamePanelShape.setPosition(centerX,centerY+uiOffset/2.0f);

    goTitleButtonShape.setPosition(centerX,centerY+50.0f);

    goTitleButtonText.setPosition(centerX,centerY+50.0f);
    //
    pauseMenuPanelShape.setPosition(centerX,centerY);
//ポーズメニューテキスト
    pauseMenuText.setPosition(centerX,uiOffset/2.0f);

    continueButtonShape.setPosition(centerX,centerY);

    continueButtonText.setPosition(centerX,centerY);
    
    finishButtonShape.setPosition(centerX,centerY+100.0f);

    finishButtonText.setPosition(centerX,centerY+100.0f);

    menuButtonShape.setPosition(static_cast<float>(newWidth-10-menuButtonShape.getSize().x),static_cast<float>(uiOffset / 2.0f - menuButtonShape.getSize().y / 2.0f));

    menuButtonText.setPosition(static_cast<float>(menuButtonShape.getPosition().x + menuButtonShape.getSize().x / 2.0f),static_cast<float>(menuButtonShape.getPosition().y + menuButtonShape.getSize().y / 2.0f));

    titleText.setPosition(centerX,uiOffset);//UI部分中央に表示

    easyButtonShape.setPosition(centerX,centerY-60.0f-50.0f);

    easyButtonText.setPosition(centerX,centerY-45.0f);

    normalButtonShape.setPosition(centerX,centerY+centerY/3-50.0f-5.0f);

    normalButtonText.setPosition(centerX,centerY+centerY/3-55.0f);

    hardButtonShape.setPosition(centerX,centerY+centerY*2/3);

    hardButtonText.setPosition(centerX,centerY+centerY*2/3-60.0f);
    //ヒントボタンとテキストの位置
    //1つ目のー１０は画面端とボックスとの余白,2つ目はメニューボックスとヒントボックスとの距離
    hintButtonShape.setPosition(static_cast<float>(newWidth-10-hintButtonShape.getSize().x-menuButtonShape.getSize().x-10),static_cast<float>(uiOffset / 2.0f - hintButtonShape.getSize().y / 2.0f));
    hintButtonText.setPosition(static_cast<float>(hintButtonShape.getPosition().x + hintButtonShape.getSize().x / 2.0f),static_cast<float>(hintButtonShape.getPosition().y + hintButtonShape.getSize().y / 2.0f));
    
    winText.setPosition(centerX,centerY);//

    gameOverText.setPosition(centerX, centerY);//UI部分中央に表示
//時間表示ボックス
    timeDisplayShape.setPosition(centerX,uiOffset/2.0f);
//Timeってテキスト
    timeBoxText.setPosition(centerX,uiOffset/3.0f);
//秒数テキスト
    timeDisplayText.setPosition(centerX,uiOffset/1.5f);

    visualGuidance_glayLine.setPosition(centerX+20.0f,centerY);

    visualGuidance_blackLine.setPosition(centerX+600.0f,centerY);

    m_reverseColorTitleText.setPosition(centerX,uiOffset);
    m_reverseColorEasyText.setPosition(centerX,centerY-45.0f);
    m_reverseColorNormalText.setPosition(centerX,centerY+centerY/3-55.0f);
    m_reverseColorHardText.setPosition(centerX,centerY+centerY*2/3-60.0f);
    m_reverseColorEasyButtonShape.setPosition(centerX,centerY-60.0f-50.0f);
    m_reverseColorNormalButtonShape.setPosition(centerX,centerY+centerY/3-50.0f-5.0f);
    m_reverseColorHardButtonShape.setPosition(centerX,centerY+centerY*2/3);

    m_overColorEasyShape.setPosition(centerX,centerY+20.0f);
    m_overColorNormalShape.setPosition(centerX,centerY+150.0f);//ボックスの縦100+ボックスのアウトライン20=120
    m_overColorHardShape.setPosition(centerX,centerY+270.0f);

    m_initialEasyButtonPos = easyButtonShape.getPosition();
    m_initialNormalButtonPos = normalButtonShape.getPosition();
    m_initialHardButtonPos = hardButtonShape.getPosition();

    createBackgroundGrid(newWidth,newHeight,80);
}
//タイマー表示
void GameUI::updateTimer(GameState currentState){
    if(currentState==GameState::Playing){
        //ポーズ時の時間と再開してからカウントした時間を合計、それを表示。
        sf::Time totalElapsedTime=elapsedTimeWhenPaused + gameClock.getElapsedTime();
        int nowSeconds=totalElapsedTime.asSeconds();
        timeDisplayText.setString(std::to_string(nowSeconds));
        sf::FloatRect timeDisplayRect = timeDisplayText.getLocalBounds();
        timeDisplayText.setOrigin(timeDisplayRect.width / 2.0f, timeDisplayRect.top + timeDisplayRect.height / 2.0f);
    }
}
//ポーズしたときの時間を保持
void GameUI::pauseTimer(){
    //ポーズしたとき経過した時間
    elapsedTimeWhenPaused+=gameClock.getElapsedTime();
}

void GameUI::continueGameTimer(){
    gameClock.restart();
}


void GameUI::startGameTimer(){
    elapsedTimeWhenPaused=sf::Time::Zero;//ポーズ画面から終了したときも時間を０に
    gameClock.restart();//sf::Clock gameClock
}

void GameUI::setFont(const sf::Font& loadedFont){
    // 左クリック説明
    leftInstructionText.setFont(loadedFont);
    // 右クリック説明
    rightInstructionText.setFont(loadedFont);
    // ゲームオーバーメッセージの設定
    gameOverText.setFont(loadedFont);
    // 勝利メッセージの設定
    winText.setFont(loadedFont);
    //メニュー押した後のポーズ画面
    pauseMenuText.setFont(loadedFont);
    //Timeをテキスト表示
    timeBoxText.setFont(loadedFont);

    
}

void GameUI::setMainFont(const sf::Font& loadedMainFont){
    //タイトルテキスト設定
    titleText.setFont(loadedMainFont);
    //以下難易度のフォント設定
    easyButtonText.setFont(loadedMainFont);
    normalButtonText.setFont(loadedMainFont);
    hardButtonText.setFont(loadedMainFont);
    //ヒントボタンのテキスト
    hintButtonText.setFont(loadedMainFont);
    // リスタートボタン
    goTitleButtonText.setFont(loadedMainFont);
    //ゲーム中のポーズボタンテキスト
    menuButtonText.setFont(loadedMainFont);
    //ポーズ中にプレイに戻るボタン
    continueButtonText.setFont(loadedMainFont);
    //ポーズ中に終了するボタン
    finishButtonText.setFont(loadedMainFont);
    //時間の表示
    timeDisplayText.setFont(loadedMainFont);

    m_reverseColorTitleText.setFont(loadedMainFont);
    m_reverseColorEasyText.setFont(loadedMainFont);
    m_reverseColorNormalText.setFont(loadedMainFont);
    m_reverseColorHardText.setFont(loadedMainFont);
}

void GameUI::initializeStyles(){
    endGamePanelShape.setSize(sf::Vector2f(400.0f, 200.0f));
    endGamePanelShape.setFillColor(sf::Color(0, 0, 0,100)); //グレー,背景透過
    endGamePanelShape.setOrigin(endGamePanelShape.getSize()/ 2.0f);
    endGamePanelShape.setOutlineThickness(5);
    endGamePanelShape.setOutlineColor(sf::Color::White);

    goTitleButtonShape.setSize(sf::Vector2f(100.0f, 30.0f));
    goTitleButtonShape.setFillColor(sf::Color(100, 100, 250)); // 青っぽい
    goTitleButtonShape.setOrigin(goTitleButtonShape.getSize() / 2.0f);
    goTitleButtonShape.setOutlineThickness(2);
    goTitleButtonShape.setOutlineColor(sf::Color::White);

    goTitleButtonText.setString("GoTitle");
    goTitleButtonText.setCharacterSize(18);
    goTitleButtonText.setFillColor(sf::Color::White);
    sf::FloatRect goTitletextBounds = goTitleButtonText.getLocalBounds();
    goTitleButtonText.setOrigin(goTitletextBounds.left + goTitletextBounds.width / 2.0f, goTitletextBounds.top + goTitletextBounds.height / 2.0f);

    pauseMenuText.setString("Puase");
    pauseMenuText.setCharacterSize(50);
    pauseMenuText.setFillColor(sf::Color::White);
    sf::FloatRect pauseRect = pauseMenuText.getLocalBounds();
    pauseMenuText.setOrigin(pauseRect.width / 2.0f, pauseRect.top + pauseRect.height / 2.0f);

    continueButtonShape.setSize(sf::Vector2f(300.0f, 60.0f));
    continueButtonShape.setFillColor(sf::Color(200,0,0)); //赤
    continueButtonShape.setOrigin(continueButtonShape.getSize() / 2.0f);
    continueButtonShape.setOutlineThickness(5);
    continueButtonShape.setOutlineColor(sf::Color::Black);

    continueButtonText.setString("CONTINUE");
    continueButtonText.setCharacterSize(30);
    continueButtonText.setFillColor(sf::Color::Black);
    sf::FloatRect continueRect = continueButtonText.getLocalBounds();
    continueButtonText.setOrigin(continueRect.left + continueRect.width / 2.0f, continueRect.top + continueRect.height / 2.0f);

    finishButtonShape.setSize(sf::Vector2f(300.0f, 60.0f));
    finishButtonShape.setFillColor(sf::Color(250,0,0)); //赤
    finishButtonShape.setOrigin(finishButtonShape.getSize().x / 2.0f,finishButtonShape.getSize().y / 2.0f);
    finishButtonShape.setOutlineThickness(5);
    finishButtonShape.setOutlineColor(sf::Color::Black);

    finishButtonText.setString("FINISH");
    finishButtonText.setCharacterSize(30);
    finishButtonText.setFillColor(sf::Color::Black);
    sf::FloatRect finishRect = finishButtonText.getLocalBounds();
    finishButtonText.setOrigin(finishRect.left + finishRect.width / 2.0f, finishRect.top + finishRect.height / 2.0f);

    menuButtonShape.setSize(sf::Vector2f(100.0f, 30.0f));
    menuButtonShape.setFillColor(sf::Color(100, 100, 250)); // 青っぽい
    menuButtonShape.setOutlineThickness(2);
    menuButtonShape.setOutlineColor(sf::Color::White);

    menuButtonText.setString("Menu");
    menuButtonText.setCharacterSize(18);
    menuButtonText.setFillColor(sf::Color::White);
    sf::FloatRect menuRect = menuButtonText.getLocalBounds();
    menuButtonText.setOrigin(menuRect.left + menuRect.width / 2.0f, menuRect.top + menuRect.height / 2.0f);

    easyButtonShape.setPointCount(4);
    easyButtonShape.setPoint(0,sf::Vector2f(0,0));
    easyButtonShape.setPoint(1,sf::Vector2f(400,30));
    easyButtonShape.setPoint(2,sf::Vector2f(420,110));
    easyButtonShape.setPoint(3,sf::Vector2f(10,100));
    easyButtonShape.setFillColor(sf::Color::White); //グレー（数字が大きいほど白)
    sf::FloatRect easyBounds=easyButtonShape.getLocalBounds();
    easyButtonShape.setOrigin(easyBounds.left+easyBounds.width/2.0f,easyBounds.top+easyBounds.height/2.0f-60.0f);
    easyButtonShape.setOutlineThickness(10);
    easyButtonShape.setOutlineColor(sf::Color::Black);

    easyButtonText.setFillColor(sf::Color(1,1,1,200));
    easyButtonText.setOutlineColor(sf::Color::Green);
    easyButtonText.setOutlineThickness(6.0f);
    easyButtonText.setCharacterSize(48);
    easyButtonText.setString("Easy"); // 静的なテキストもここで設定
    sf::FloatRect easyRect = easyButtonText.getLocalBounds();
    easyButtonText.setOrigin(easyRect.width / 2.0f, easyRect.top + easyRect.height / 2.0f);

    normalButtonShape.setPointCount(4);

    normalButtonShape.setPoint(0,sf::Vector2f(0,0));
    normalButtonShape.setPoint(1,sf::Vector2f(400,20));
    normalButtonShape.setPoint(2,sf::Vector2f(430,110));
    normalButtonShape.setPoint(3,sf::Vector2f(10,100));
    sf::FloatRect normalBounds=normalButtonShape.getLocalBounds();
    normalButtonShape.setFillColor(sf::Color::White); //グレー
    normalButtonShape.setOrigin(normalBounds.left+normalBounds.width/2.0f,normalBounds.top+normalBounds.height/2.0f);
    normalButtonShape.setOutlineThickness(10);
    normalButtonShape.setOutlineColor(sf::Color::Black);

    normalButtonText.setFillColor(sf::Color(1,1,1,200));
    normalButtonText.setOutlineColor(sf::Color::Blue);
    normalButtonText.setOutlineThickness(6.0f);
    normalButtonText.setCharacterSize(48);
    normalButtonText.setString("Normal");
    sf::FloatRect normalRect = normalButtonText.getLocalBounds();
    normalButtonText.setOrigin(normalRect.left + normalRect.width / 2.0f, normalRect.top + normalRect.height / 2.0f);

    hardButtonShape.setPointCount(4);
    hardButtonShape.setPoint(0,sf::Vector2f(0,0));
    hardButtonShape.setPoint(1,sf::Vector2f(400,20));
    hardButtonShape.setPoint(2,sf::Vector2f(430,110));
    hardButtonShape.setPoint(3,sf::Vector2f(10,100));
    sf::FloatRect hardBounds=hardButtonShape.getLocalBounds();
    hardButtonShape.setFillColor(sf::Color::White); //グレー
    hardButtonShape.setOrigin(hardBounds.left+hardBounds.width/2.0f,hardBounds.top+hardBounds.height/2.0f+60.0f);
    hardButtonShape.setOutlineThickness(10);
    hardButtonShape.setOutlineColor(sf::Color::Black);

    hardButtonText.setFillColor(sf::Color::Black);
    hardButtonText.setOutlineColor(sf::Color::Red);
    hardButtonText.setOutlineThickness(6.0f);
    hardButtonText.setCharacterSize(48);
    hardButtonText.setString("Hard");
    sf::FloatRect hardRect = hardButtonText.getLocalBounds();
    hardButtonText.setOrigin(hardRect.left+hardRect.width/2.0f,hardRect.top+hardRect.height/2.0f);

    titleText.setFillColor(sf::Color::Black);
    titleText.setOutlineColor(sf::Color::White);
    titleText.setOutlineThickness(20.0f);
    titleText.setCharacterSize(120);
    titleText.setString("MyMineSweeper");
    sf::FloatRect titleRect = titleText.getLocalBounds();
    titleText.setOrigin(titleRect.width/2.0f,titleRect.top + titleRect.height / 2.0f);

    winText.setString("You Win!");
    winText.setCharacterSize(48);
    winText.setFillColor(sf::Color::Green);
    sf::FloatRect winRect=winText.getLocalBounds();
    winText.setOrigin(winRect.width/2.0f,winRect.top+winRect.height/2.0f);

    gameOverText.setString("Game Over!");
    gameOverText.setCharacterSize(30); //サイズ
    gameOverText.setFillColor(sf::Color::Red);
    sf::FloatRect goRect=gameOverText.getLocalBounds();
    gameOverText.setOrigin(goRect.width/2.0f,goRect.top+goRect.height/2.0f);
    
    timeDisplayShape.setSize(sf::Vector2f(200.0f, 100.0f));//横200、縦100
    timeDisplayShape.setFillColor(sf::Color(100, 100, 100)); //ボックス内の色、黒            timeDisplayShape.setOrigin(timeDisplayShape.getSize().x / 2.0f,timeDisplayShape.getSize().y / 2.0f);
    timeDisplayShape.setOutlineThickness(2);
    timeDisplayShape.setOrigin(timeDisplayShape.getSize() / 2.0f);
    timeDisplayShape.setOutlineColor(sf::Color::White);

    timeBoxText.setCharacterSize(30);
    timeBoxText.setFillColor(sf::Color::White);
    timeBoxText.setString("Time");
    sf::FloatRect timeBoxRect = timeBoxText.getLocalBounds();
    timeBoxText.setOrigin(timeBoxRect.width / 2.0f, timeBoxRect.top + timeBoxRect.height / 2.0f);

    timeDisplayText.setCharacterSize(30);
    timeDisplayText.setFillColor(sf::Color::White);
    timeDisplayText.setString("0");//いったん適当なものをいれて以下で原点を合わせられるように
    sf::FloatRect timeDisplayRect = timeDisplayText.getLocalBounds();
    timeDisplayText.setOrigin(timeDisplayRect.width / 2.0f, timeDisplayRect.top + timeDisplayRect.height / 2.0f);

    hintButtonShape.setSize(sf::Vector2f(50.0f, 30.0f));//横50、縦30
    hintButtonShape.setFillColor(sf::Color(100, 100, 100)); //ボックス内の色、グレー
    hintButtonShape.setOutlineThickness(2);
    hintButtonShape.setOutlineColor(sf::Color::White);

    hintButtonText.setCharacterSize(20);
    hintButtonText.setFillColor(sf::Color::White);
    hintButtonText.setString("Hint");
    sf::FloatRect hintButtonRect = hintButtonText.getLocalBounds();
    hintButtonText.setOrigin(hintButtonRect.width / 2.0f, hintButtonRect.top + hintButtonRect.height / 2.0f);

    m_hintHighlight.setSize(sf::Vector2f(50.0f,50.0f));//1マスの大きさ
    m_hintHighlight.setFillColor(sf::Color(10, 100, 200, 200)); //ボックス内の色,デフォルトの色
    m_hintHighlight.setOutlineThickness(2);
    m_hintHighlight.setOutlineColor(sf::Color::Blue);


    visualGuidance_glayLine.setSize(sf::Vector2f(20.0f,2000.0f));
    visualGuidance_glayLine.setFillColor(sf::Color(100,100,100,200));
    visualGuidance_glayLine.setOrigin(visualGuidance_glayLine.getSize().x/2.0f,visualGuidance_glayLine.getSize().y/2.0f);
    visualGuidance_glayLine.setRotation(30.0f);

    visualGuidance_blackLine.setSize(sf::Vector2f(1000.0f,2000.0f));
    visualGuidance_blackLine.setFillColor(sf::Color(0,0,0));
    visualGuidance_blackLine.setOrigin(visualGuidance_blackLine.getSize().x/2.0f,visualGuidance_blackLine.getSize().y/2.0f);
    visualGuidance_blackLine.setRotation(30.0f);

    m_reverseColorTitleText.setFillColor(sf::Color::White);
    m_reverseColorTitleText.setOutlineColor(sf::Color::Black);
    m_reverseColorTitleText.setOutlineThickness(20.0f);
    m_reverseColorTitleText.setCharacterSize(120);
    m_reverseColorTitleText.setString("MyMineSweeper");
    sf::FloatRect m_reverseColorTitleRect = m_reverseColorTitleText.getLocalBounds();
    m_reverseColorTitleText.setOrigin(m_reverseColorTitleRect.width/2.0f,m_reverseColorTitleRect.top + m_reverseColorTitleRect.height / 2.0f);

    m_reverseColorEasyText.setFillColor(sf::Color(50,255,50));
    m_reverseColorEasyText.setOutlineColor(sf::Color(1,1,1,200));
    m_reverseColorEasyText.setOutlineThickness(6.0f);
    m_reverseColorEasyText.setCharacterSize(48);
    m_reverseColorEasyText.setString("Easy");
    sf::FloatRect m_reverseColorEasyRect = m_reverseColorEasyText.getLocalBounds();
    m_reverseColorEasyText.setOrigin(m_reverseColorEasyRect.width / 2.0f, m_reverseColorEasyRect.top + m_reverseColorEasyRect.height / 2.0f);

    m_reverseColorNormalText.setFillColor(sf::Color(50,50,255));
    m_reverseColorNormalText.setOutlineColor(sf::Color(1,1,1,200));
    m_reverseColorNormalText.setOutlineThickness(6.0f);
    m_reverseColorNormalText.setCharacterSize(48);
    m_reverseColorNormalText.setString("Normal");
    sf::FloatRect m_reverseColorNormalRect = m_reverseColorNormalText.getLocalBounds();
    m_reverseColorNormalText.setOrigin(m_reverseColorNormalRect.left + m_reverseColorNormalRect.width / 2.0f, m_reverseColorNormalRect.top + m_reverseColorNormalRect.height / 2.0f);

    m_reverseColorHardText.setFillColor(sf::Color(255,50,50));
    m_reverseColorHardText.setOutlineColor(sf::Color(1,1,1,200));
    m_reverseColorHardText.setOutlineThickness(6.0f);
    m_reverseColorHardText.setCharacterSize(48);
    m_reverseColorHardText.setString("Hard");
    sf::FloatRect m_reverseColorHardRect = m_reverseColorHardText.getLocalBounds();
    m_reverseColorHardText.setOrigin(m_reverseColorHardRect.left + m_reverseColorHardRect.width / 2.0f, m_reverseColorHardRect.top + m_reverseColorHardRect.height / 2.0f);

    m_reverseColorEasyButtonShape.setPointCount(4);
    m_reverseColorEasyButtonShape.setPoint(0,sf::Vector2f(0,0));
    m_reverseColorEasyButtonShape.setPoint(1,sf::Vector2f(400,30));
    m_reverseColorEasyButtonShape.setPoint(2,sf::Vector2f(420,110));
    m_reverseColorEasyButtonShape.setPoint(3,sf::Vector2f(10,100));
    m_reverseColorEasyButtonShape.setFillColor(sf::Color(10,100,200));
    sf::FloatRect reverseColrEasyBounds=m_reverseColorEasyButtonShape.getLocalBounds();
    m_reverseColorEasyButtonShape.setOrigin(reverseColrEasyBounds.left+reverseColrEasyBounds.width/2.0f,reverseColrEasyBounds.top+reverseColrEasyBounds.height/2.0f-60.0f);
    m_reverseColorEasyButtonShape.setOutlineThickness(10);
    m_reverseColorEasyButtonShape.setOutlineColor(sf::Color::Black);

    m_reverseColorNormalButtonShape.setPointCount(4);
    m_reverseColorNormalButtonShape.setPoint(0,sf::Vector2f(0,0));
    m_reverseColorNormalButtonShape.setPoint(1,sf::Vector2f(400,20));
    m_reverseColorNormalButtonShape.setPoint(2,sf::Vector2f(430,110));
    m_reverseColorNormalButtonShape.setPoint(3,sf::Vector2f(10,95));
    sf::FloatRect reverseColrNormalBounds=m_reverseColorNormalButtonShape.getLocalBounds();
    m_reverseColorNormalButtonShape.setFillColor(sf::Color(10,100,200)); //グレー
    m_reverseColorNormalButtonShape.setOrigin(reverseColrNormalBounds.left+reverseColrNormalBounds.width/2.0f,reverseColrNormalBounds.top+reverseColrNormalBounds.height/2.0f);
    m_reverseColorNormalButtonShape.setOutlineThickness(10);
    m_reverseColorNormalButtonShape.setOutlineColor(sf::Color::Black);

    m_reverseColorHardButtonShape.setPointCount(4);
    m_reverseColorHardButtonShape.setPoint(0,sf::Vector2f(0,0));
    m_reverseColorHardButtonShape.setPoint(1,sf::Vector2f(400,20));
    m_reverseColorHardButtonShape.setPoint(2,sf::Vector2f(430,110));
    m_reverseColorHardButtonShape.setPoint(3,sf::Vector2f(10,100));
    sf::FloatRect reverseColrHardBounds=m_reverseColorHardButtonShape.getLocalBounds();
    m_reverseColorHardButtonShape.setFillColor(sf::Color(10,100,200)); //グレー
    m_reverseColorHardButtonShape.setOrigin(reverseColrHardBounds.left+reverseColrHardBounds.width/2.0f,reverseColrHardBounds.top+reverseColrHardBounds.height/2.0f+60.0f);
    m_reverseColorHardButtonShape.setOutlineThickness(10);
    m_reverseColorHardButtonShape.setOutlineColor(sf::Color::Black);

    m_overColorEasyShape.setPointCount(4);
    m_overColorEasyShape.setPoint(0,sf::Vector2f(0,0));
    m_overColorEasyShape.setPoint(1,sf::Vector2f(396,-17));
    m_overColorEasyShape.setPoint(2,sf::Vector2f(403,93));
    m_overColorEasyShape.setPoint(3,sf::Vector2f(-22,118));
    sf::FloatRect overColorEasyBounds=m_overColorEasyShape.getLocalBounds();
    m_overColorEasyShape.setFillColor(sf::Color(200,200,200,100));
    m_overColorEasyShape.setOrigin(overColorEasyBounds.left+overColorEasyBounds.width/2.0f,overColorEasyBounds.top+overColorEasyBounds.height/2.0f+60.0f);

    m_overColorNormalShape.setPointCount(4);
    m_overColorNormalShape.setPoint(0,sf::Vector2f(0,0));
    m_overColorNormalShape.setPoint(1,sf::Vector2f(420,-18));
    m_overColorNormalShape.setPoint(2,sf::Vector2f(411,93));
    m_overColorNormalShape.setPoint(3,sf::Vector2f(-15,113));
    sf::FloatRect overColorNormalBounds=m_overColorNormalShape.getLocalBounds();
    m_overColorNormalShape.setFillColor(sf::Color(200,200,200,100));
    m_overColorNormalShape.setOrigin(overColorNormalBounds.left+overColorNormalBounds.width/2.0f,overColorNormalBounds.top+overColorNormalBounds.height/2.0f+60.0f);

    m_overColorHardShape.setPointCount(4);
    m_overColorHardShape.setPoint(0,sf::Vector2f(0,0));
    m_overColorHardShape.setPoint(1,sf::Vector2f(415,-10));
    m_overColorHardShape.setPoint(2,sf::Vector2f(404,93));
    m_overColorHardShape.setPoint(3,sf::Vector2f(-6,110));
    sf::FloatRect overColorHardBounds=m_overColorHardShape.getLocalBounds();
    m_overColorHardShape.setFillColor(sf::Color(200,200,200,100));
    m_overColorHardShape.setOrigin(overColorHardBounds.left+overColorHardBounds.width/2.0f,overColorHardBounds.top+overColorHardBounds.height/2.0f+60.0f);

    if(!m_clipperShader.loadFromFile("assets/shaders/clipper.frag",sf::Shader::Fragment)){
        std::cout<<"Error loading shader"<<std::endl;
    }
    if(!m_shapeClipperShader.loadFromFile("assets/shaders/shape_clipper.frag",sf::Shader::Fragment)){
        std::cout<<"Error loading shape shader"<<std::endl;
    }
}

void GameUI::showHint(sf::Vector2i pos){
    m_isShowingHint = true;
    float safeCellX=pos.y*50;
    float safeCellY=pos.x*50;
    m_hintHighlight.setPosition(safeCellX, safeCellY+uiOffset);
}

void GameUI::deleteHint(){
    m_isShowingHint=false;
}

void GameUI::Draw(sf::RenderWindow& window, GameState currentState)const{
    if(currentState==GameState::Playing){
        window.draw(menuButtonShape);
        window.draw(menuButtonText);
        window.draw(timeDisplayShape);
        window.draw(timeBoxText);
        window.draw(timeDisplayText);
        window.draw(hintButtonShape);
        window.draw(hintButtonText);
        //ヒントボタン押したとき
        if(m_isShowingHint){
            window.draw(m_hintHighlight);
        }

    }else if(currentState==GameState::PauseMenu){
        window.clear(sf::Color(100,100,100,200));
        window.draw(pauseMenuText);
        window.draw(continueButtonShape);
        window.draw(continueButtonText);
        window.draw(finishButtonShape);
        window.draw(finishButtonText);
        
    }else if(currentState==GameState::MainMenu){
        window.draw(visualGuidance_glayLine);
        window.draw(visualGuidance_blackLine);
        
    // 1. 基準点として、ウィンドウの中心を取得
        sf::Vector2f center(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

    // 2. 直線の「傾き」をベクトルで定義する
    //    (x, y) = (横に1進むと, 縦にどれだけ進むか)
    //    Y座標は下向きなので、右上がりの傾きは Y がマイナスになります。
        sf::Vector2f slopeVector(-1.0f, -1.73f); //左に1進むと、下に1.73進む傾き

    // 3. 基準点と傾きから、境界線の2点を計算する
    //(非常に大きな数値を掛けて、線が必ず画面を横切るようにする)
        sf::Vector2f linePoint1 = center + slopeVector * 10000.0f;
        sf::Vector2f linePoint2 = center - slopeVector * 10000.0f;

        float a=linePoint2.y-linePoint1.y;
        float b=linePoint1.x-linePoint2.x;
        float c=linePoint2.x*linePoint1.y-linePoint2.y*linePoint1.x;

        m_clipperShader.setUniform("lineA",a);
        m_clipperShader.setUniform("lineB",b);
        m_clipperShader.setUniform("lineC",c);
        sf::RenderStates states;
        states.shader=&m_clipperShader;
    
        m_shapeClipperShader.setUniform("lineA",a);
        m_shapeClipperShader.setUniform("lineB",b);
        m_shapeClipperShader.setUniform("lineC",c);
        sf::RenderStates shapeStates;
        shapeStates.shader=&m_shapeClipperShader;

    //背景のグリッド
        window.draw(m_backgroundGrid);

    //タイトルテキスト
        window.draw(titleText);
        window.draw(m_reverseColorTitleText,states);
        
    //Easyのボタンテキスト
        window.draw(easyButtonShape);
        window.draw(m_reverseColorEasyButtonShape,shapeStates);
        window.draw(easyButtonText);
        window.draw(m_reverseColorEasyText,states);
        if(m_isEasyButtonHovered){
            window.draw(m_overColorEasyShape);
        }

    //Normalのボタンテキスト
        window.draw(normalButtonShape);
        window.draw(m_reverseColorNormalButtonShape,shapeStates);
        window.draw(normalButtonText);
        window.draw(m_reverseColorNormalText,states);
        if(m_isNormalButtonHovered){
            window.draw(m_overColorNormalShape);
        }

    //Hardのボタンテキスト
        window.draw(hardButtonShape);
        window.draw(m_reverseColorHardButtonShape,shapeStates);
        window.draw(hardButtonText);
        window.draw(m_reverseColorHardText,states);
        if(m_isHardButtonHovered){
            window.draw(m_overColorHardShape);
        }

    }else{
        //GameOverかWin時のテキストやボックス
        window.draw(timeDisplayShape);
        window.draw(timeBoxText);
        window.draw(timeDisplayText);
        window.draw(endGamePanelShape);
        window.draw(goTitleButtonShape); 
        window.draw(goTitleButtonText);
        if (currentState == GameState::GameOver){
            window.draw(gameOverText);
        }else{
            window.draw(winText);
        }
    }
}

void GameUI::updateHoverState(const sf::Vector2i& mousePos,GameState currentState){
    if(currentState==GameState::MainMenu){
        bool isAnyButtonHovered=false;
        float time=m_hoverClock.getElapsedTime().asSeconds();
        float amplitude=5.0f;
        float velocity=5.0f;
        float yOffset=std::sin(time*amplitude)*velocity;//
    //Easyのホバー
        if(isEasyButtonClicked(mousePos)){
            easyButtonShape.setScale(1.05f,1.05f);
            m_reverseColorEasyButtonShape.setScale(1.05f,1.05f);
            easyButtonText.setScale(1.05f,1.05f);
            m_reverseColorEasyText.setScale(1.05f,1.05f);
            isAnyButtonHovered=true;
            m_isEasyButtonHovered=true;

            easyButtonShape.setPosition(m_initialEasyButtonPos.x, m_initialEasyButtonPos.y + yOffset);
            m_reverseColorEasyButtonShape.setPosition(m_initialEasyButtonPos.x, m_initialEasyButtonPos.y + yOffset);

            m_overColorEasyShape.setScale(1.05f,1.05f);
        }else{
            m_isEasyButtonHovered=false;
            easyButtonShape.setScale(1.0f,1.0f);
            m_reverseColorEasyButtonShape.setScale(1.0f,1.0f);
            easyButtonText.setScale(1.0f,1.0f);
            m_reverseColorEasyText.setScale(1.0f,1.0f);
            easyButtonShape.setPosition(m_initialEasyButtonPos);
            m_reverseColorEasyButtonShape.setPosition(m_initialEasyButtonPos);
        }
    //Nomalのホバー
        if(isNormalButtonClicked(mousePos)){
            normalButtonShape.setScale(1.05f,1.05f);
            m_reverseColorNormalButtonShape.setScale(1.05f,1.05f);
            normalButtonText.setScale(1.05f,1.05f);
            m_reverseColorNormalText.setScale(1.05f,1.05f);
            isAnyButtonHovered=true;
            m_isNormalButtonHovered = true;

            normalButtonShape.setPosition(m_initialNormalButtonPos.x, m_initialNormalButtonPos.y + yOffset);
            m_reverseColorNormalButtonShape.setPosition(m_initialNormalButtonPos.x, m_initialNormalButtonPos.y + yOffset);
        }else{
            m_isNormalButtonHovered = false;
            normalButtonShape.setScale(1.0f,1.0f);
            m_reverseColorNormalButtonShape.setScale(1.0f,1.0f);
            normalButtonText.setScale(1.0f,1.0f);
            m_reverseColorNormalText.setScale(1.0f,1.0f);
            normalButtonShape.setPosition(m_initialNormalButtonPos);
            m_reverseColorNormalButtonShape.setPosition(m_initialNormalButtonPos);
        }
    //Hardのホバー
        if(isHardButtonClicked(mousePos)){
            hardButtonShape.setScale(1.05f,1.05f);
            m_reverseColorHardButtonShape.setScale(1.05f,1.05f);
            hardButtonText.setScale(1.05f,1.05f);
            m_reverseColorHardText.setScale(1.05f,1.05f);
            isAnyButtonHovered=true;
            m_isHardButtonHovered = true;

            hardButtonShape.setPosition(m_initialHardButtonPos.x, m_initialHardButtonPos.y + yOffset);
            m_reverseColorHardButtonShape.setPosition(m_initialHardButtonPos.x, m_initialHardButtonPos.y + yOffset);
        }else{
            m_isHardButtonHovered = false;
            hardButtonShape.setScale(1.0f,1.0f);
            m_reverseColorHardButtonShape.setScale(1.0f,1.0f);
            hardButtonText.setScale(1.0f,1.0f);
            m_reverseColorHardText.setScale(1.0f,1.0f);
            hardButtonShape.setPosition(m_initialHardButtonPos);
            m_reverseColorHardButtonShape.setPosition(m_initialHardButtonPos);
        }
        if(!isAnyButtonHovered){
            m_hoverClock.restart();
        }
    }
}

void GameUI::createBackgroundGrid(unsigned int windowWodth,unsigned int windowHeight,int spacing){
    m_backgroundGrid.setPrimitiveType(sf::Lines);
    m_backgroundGrid.clear();
    std::cout<<"create"<<std::endl;
    sf::Color gridColor(255,255,255,30);

    //垂直線
    for(int x=0;x<=windowWidth;x+=spacing){
        //垂直線の上端
        m_backgroundGrid.append(sf::Vertex(sf::Vector2f(x,0),gridColor));
        //垂直線の下端
        m_backgroundGrid.append(sf::Vertex(sf::Vector2f(x,windowHeight),gridColor));
    }
    //spacing=0;
    //平行線
    for(int y=0;y<=windowHeight;y+=spacing){
        //平行線の上端
        m_backgroundGrid.append(sf::Vertex(sf::Vector2f(0,y),gridColor));
        //平行線の下端
        m_backgroundGrid.append(sf::Vertex(sf::Vector2f(windowWidth,y),gridColor));
    }
}

// マウス位置がボタンの描画領域内にあるかを判定
bool GameUI::isGoTitleButtonClicked(const sf::Vector2i& mousePos)const{
    return goTitleButtonShape.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

bool GameUI::isMenuButtonClicked(const sf::Vector2i& mousePos)const{
    return menuButtonShape.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

bool GameUI::isContinueButtonClicked(const sf::Vector2i& mousePos)const{
    return continueButtonShape.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

bool GameUI::isFinishButtonClicked(const sf::Vector2i& mousePos)const{
    return finishButtonShape.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

bool GameUI::isEasyButtonClicked(const sf::Vector2i& mousePos)const{
    return easyButtonShape.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

bool GameUI::isNormalButtonClicked(const sf::Vector2i& mousePos)const{
    return normalButtonShape.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

bool GameUI::isHardButtonClicked(const sf::Vector2i& mousePos)const{
    return hardButtonShape.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

bool GameUI::isHintButtonCliced(const sf::Vector2i& mousePos)const{
    return hintButtonShape.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}