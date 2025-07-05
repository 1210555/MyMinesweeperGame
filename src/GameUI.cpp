#include "GameUI.hpp" // 対応するヘッダーファイルをインクルード

GameUI::GameUI(int windowWidth, int windowHeight, int offset): windowWidth(windowWidth), windowHeight(windowHeight), uiOffset(offset) {
    // リスタートボタンの形状の初期化
    restartButtonShape.setSize(sf::Vector2f(100.0f, 30.0f));
    restartButtonShape.setFillColor(sf::Color(100, 100, 250)); // 青っぽい
    restartButtonShape.setOutlineThickness(2);
    restartButtonShape.setOutlineColor(sf::Color::White);
    restartButtonShape.setPosition(static_cast<float>(windowWidth - 10 - restartButtonShape.getSize().x),static_cast<float>(uiOffset / 2.0f - restartButtonShape.getSize().y / 2.0f));

    continueButtonShape.setSize(sf::Vector2f(100.0f, 30.0f));
    continueButtonShape.setFillColor(sf::Color(100, 100, 250)); // 青っぽい
    continueButtonShape.setOutlineThickness(2);
    continueButtonShape.setOutlineColor(sf::Color::White);
    continueButtonShape.setPosition(windowWidth/2.0f,static_cast<float>(uiOffset / 2.0f - continueButtonShape.getSize().y / 2.0f));

    finishButtonShape.setSize(sf::Vector2f(100.0f, 30.0f));
    finishButtonShape.setFillColor(sf::Color(100, 100, 250)); // 青っぽい
    finishButtonShape.setOutlineThickness(2);
    finishButtonShape.setOutlineColor(sf::Color::White);
    finishButtonShape.setPosition(windowWidth/2.0f,static_cast<float>(uiOffset / 2.0f - restartButtonShape.getSize().y / 2.0f));

    menuButtonShape.setSize(sf::Vector2f(100.0f, 30.0f));
    menuButtonShape.setFillColor(sf::Color(100, 100, 250)); // 青っぽい
    menuButtonShape.setOutlineThickness(2);
    menuButtonShape.setOutlineColor(sf::Color::White);
    menuButtonShape.setPosition(static_cast<float>(windowWidth - 10 - menuButtonShape.getSize().x),static_cast<float>(uiOffset / 2.0f - menuButtonShape.getSize().y / 2.0f));

    easyButtonShape.setSize(sf::Vector2f(400.0f, 100.0f));
    easyButtonShape.setFillColor(sf::Color(100, 100, 250)); // 青っぽい
    easyButtonShape.setOrigin(easyButtonShape.getSize().x / 2.0f,easyButtonShape.getSize().y / 2.0f-60.0f);
    easyButtonShape.setOutlineThickness(2);
    easyButtonShape.setOutlineColor(sf::Color::Red);
    easyButtonShape.setPosition(windowWidth/2.0f,windowHeight/2.0f-150.0f-uiOffset);

    normalButtonShape.setSize(sf::Vector2f(400.0f, 100.0f));
    normalButtonShape.setFillColor(sf::Color(100, 100, 250)); // 青っぽい
    normalButtonShape.setOrigin(normalButtonShape.getSize() / 2.0f);
    normalButtonShape.setOutlineThickness(2);
    normalButtonShape.setOutlineColor(sf::Color::White);
    normalButtonShape.setPosition(windowWidth/2.0f,windowHeight/2.0f-uiOffset);

    difficultButtonShape.setSize(sf::Vector2f(400.0f, 100.0f));
    difficultButtonShape.setFillColor(sf::Color(100, 100, 250)); // 青っぽい
    difficultButtonShape.setOrigin(difficultButtonShape.getSize().x / 2.0f,difficultButtonShape.getSize().y / 2.0f+60.0f);
    difficultButtonShape.setOutlineThickness(2);
    difficultButtonShape.setOutlineColor(sf::Color::Green);
    difficultButtonShape.setPosition(windowWidth/2.0f,windowHeight/2.0f+150.0f-uiOffset);

}

void GameUI::setFont(const sf::Font& loadedFont){
    // 左クリック説明
    leftInstructionText.setFont(loadedFont);
    leftInstructionText.setString("Left Click: Open Tile");
    leftInstructionText.setCharacterSize(20);
    leftInstructionText.setFillColor(sf::Color::White);
    leftInstructionText.setPosition(10.0f, 10.0f);

    // 右クリック説明
    rightInstructionText.setFont(loadedFont);
    rightInstructionText.setString("Right Click: Flag Tile");
    rightInstructionText.setCharacterSize(20);
    rightInstructionText.setFillColor(sf::Color::White);
    rightInstructionText.setPosition(10.0f, 40.0f);

    // ゲームオーバーメッセージの設定
    gameOverText.setFont(loadedFont);
    gameOverText.setString("Game Over!");
    gameOverText.setCharacterSize(30); // サイズ
    gameOverText.setFillColor(sf::Color::Red);
    sf::FloatRect goRect = gameOverText.getLocalBounds();
    gameOverText.setOrigin(goRect.width / 2.0f, goRect.top + goRect.height / 2.0f);
    gameOverText.setPosition(windowWidth/2.0f , uiOffset / 2);//UI部分中央に表示

    // 勝利メッセージの設定
    winText.setFont(loadedFont);
    winText.setString("You Win!");
    winText.setCharacterSize(48);
    winText.setFillColor(sf::Color::Green);
    sf::FloatRect winRect = winText.getLocalBounds();
    winText.setOrigin(winRect.width/2.0f,winRect.top + winRect.height / 2.0f);
    winText.setPosition(windowWidth/2.0f,uiOffset/2);//UI部分中央に表示

    //タイトルテキスト設定
    titleText.setFont(loadedFont);
    titleText.setString("MyMineSweeper");
    titleText.setCharacterSize(60);
    titleText.setFillColor(sf::Color::Green);
    sf::FloatRect titleRect = titleText.getLocalBounds();
    titleText.setOrigin(titleRect.width/2.0f,titleRect.top + titleRect.height / 2.0f);
    titleText.setPosition(windowWidth/2.0f,uiOffset/2.0f);//UI部分中央に表示

    // リスタートボタン
    restartButtonText.setFont(loadedFont);
    restartButtonText.setString("RESTART");
    restartButtonText.setCharacterSize(18);
    restartButtonText.setFillColor(sf::Color::White);
    sf::FloatRect textBounds = restartButtonText.getLocalBounds();
    restartButtonText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    restartButtonText.setPosition(static_cast<float>(restartButtonShape.getPosition().x + restartButtonShape.getSize().x / 2.0f),static_cast<float>(restartButtonShape.getPosition().y + restartButtonShape.getSize().y / 2.0f));

    //ゲーム中のポーズボタンテキスト
    menuButtonText.setFont(loadedFont);
    menuButtonText.setString("Menu");
    menuButtonText.setCharacterSize(18);
    menuButtonText.setFillColor(sf::Color::White);
    sf::FloatRect menuRect = menuButtonText.getLocalBounds();
    menuButtonText.setOrigin(menuRect.left + menuRect.width / 2.0f, menuRect.top + menuRect.height / 2.0f);
    menuButtonText.setPosition(static_cast<float>(menuButtonShape.getPosition().x + menuButtonShape.getSize().x / 2.0f),static_cast<float>(menuButtonShape.getPosition().y + menuButtonShape.getSize().y / 2.0f));
 
    //メニュー押した後のポーズ画面
    pauseMenuText.setFont(loadedFont);
    pauseMenuText.setString("Puase");
    pauseMenuText.setCharacterSize(30);
    pauseMenuText.setFillColor(sf::Color::White);
    sf::FloatRect pauseRect = pauseMenuText.getLocalBounds();
    pauseMenuText.setOrigin(pauseRect.left + pauseRect.width / 2.0f, pauseRect.top + pauseRect.height / 2.0f);
    pauseMenuText.setPosition(windowWidth/2.0f,uiOffset/2.0f);
    //ポーズ中にプレイに戻るボタン
    continueButtonText.setFont(loadedFont);
    continueButtonText.setString("CONTINUE");
    continueButtonText.setCharacterSize(18);
    continueButtonText.setFillColor(sf::Color::White);
    sf::FloatRect coutinueRect = continueButtonText.getLocalBounds();
    continueButtonText.setOrigin(coutinueRect.left + coutinueRect.width / 2.0f, coutinueRect.top + coutinueRect.height / 2.0f);
    continueButtonText.setPosition(static_cast<float>(continueButtonShape.getPosition().x + continueButtonShape.getSize().x / 2.0f),static_cast<float>(continueButtonShape.getPosition().y + continueButtonShape.getSize().y / 2.0f));

    //ポーズ中に終了するボタン
    finishButtonText.setFont(loadedFont);
    finishButtonText.setString("FINISH");
    finishButtonText.setCharacterSize(18);
    finishButtonText.setFillColor(sf::Color::White);
    sf::FloatRect finishRect = finishButtonText.getLocalBounds();
    finishButtonText.setOrigin(finishRect.left + finishRect.width / 2.0f, finishRect.top + finishRect.height / 2.0f);
    finishButtonText.setPosition(static_cast<float>(finishButtonShape.getPosition().x + finishButtonShape.getSize().x / 2.0f),static_cast<float>(finishButtonShape.getPosition().y + finishButtonShape.getSize().y / 2.0f));

    //以下難易度選択
    easyButtonText.setFont(loadedFont);
    easyButtonText.setString("Easy");
    easyButtonText.setCharacterSize(48);
    easyButtonText.setFillColor(sf::Color::White);
    sf::FloatRect easyRect = easyButtonText.getLocalBounds();
    easyButtonText.setOrigin(easyRect.left + easyRect.width / 2.0f, easyRect.top + easyRect.height / 2.0f);
    easyButtonText.setPosition(windowWidth/2.0f,windowHeight/2.0f-100.0f-uiOffset);

    normalButtonText.setFont(loadedFont);
    normalButtonText.setString("Normal");
    normalButtonText.setCharacterSize(48);
    normalButtonText.setFillColor(sf::Color::White);
    sf::FloatRect normalRect = normalButtonText.getLocalBounds();
    normalButtonText.setOrigin(normalRect.left + normalRect.width / 2.0f, normalRect.top + normalRect.height / 2.0f);
    normalButtonText.setPosition(windowWidth/2.0f,windowHeight/2.0f-uiOffset);

    difficultButtonText.setFont(loadedFont);
    difficultButtonText.setString("Difficult");
    difficultButtonText.setCharacterSize(48);
    difficultButtonText.setFillColor(sf::Color::White);
    sf::FloatRect difficultRect = difficultButtonText.getLocalBounds();
    difficultButtonText.setOrigin(difficultRect.left + difficultRect.width / 2.0f, difficultRect.top + difficultRect.height / 2.0f);
    difficultButtonText.setPosition(windowWidth/2.0f,windowHeight/2.0f+100.0f-uiOffset);
}

void GameUI::Draw(sf::RenderWindow& window, GameState currentState) const {
    // Playingのみ操作説明テキストを描画
    if (currentState == GameState::Playing) {
        window.draw(leftInstructionText);
        window.draw(rightInstructionText);
        window.draw(menuButtonShape);
        window.draw(menuButtonText);
    }else if(currentState==GameState::MainMenu){
        window.draw(titleText);
        window.draw(easyButtonShape);
        window.draw(easyButtonText);
        window.draw(normalButtonShape);
        window.draw(normalButtonText);
        window.draw(difficultButtonShape);
        window.draw(difficultButtonText);
    }else if(currentState==GameState::PauseMenu){
        window.draw(pauseMenuText);
        window.draw(continueButtonShape);
        window.draw(continueButtonText);
        window.draw(finishButtonShape);
        window.draw(finishButtonText);
    }
    if (currentState == GameState::GameOver || currentState == GameState::Win || currentState == GameState::Ready) {
        window.draw(restartButtonShape); 
        window.draw(restartButtonText);

        if (currentState == GameState::GameOver){
            window.draw(gameOverText);
        }else if (currentState == GameState::Win){
            window.draw(winText);
        }
    }
}

bool GameUI::isRestartButtonClicked(const sf::Vector2i& mousePos) const {
    // マウス位置がボタンの描画領域内にあるかを判定
    return restartButtonShape.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}
bool GameUI::isMenuButtonClicked(const sf::Vector2i& mousePos) const {
    // マウス位置がボタンの描画領域内にあるかを判定
    return menuButtonShape.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}
bool GameUI::isContinueButtonClicked(const sf::Vector2i& mousePos) const {
    // マウス位置がボタンの描画領域内にあるかを判定
    return continueButtonShape.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}
bool GameUI::isFinishButtonClicked(const sf::Vector2i& mousePos) const {
    // マウス位置がボタンの描画領域内にあるかを判定
    return finishButtonShape.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}
bool GameUI::isEasyButtonClicked(const sf::Vector2i& mousePos) const {
    // マウス位置がボタンの描画領域内にあるかを判定
    return easyButtonShape.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}
bool GameUI::isNormalButtonClicked(const sf::Vector2i& mousePos) const {
    // マウス位置がボタンの描画領域内にあるかを判定
    return normalButtonShape.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}
bool GameUI::isDifficultButtonClicked(const sf::Vector2i& mousePos) const {
    // マウス位置がボタンの描画領域内にあるかを判定
    return difficultButtonShape.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}