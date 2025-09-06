#ifndef GAMEUI_HPPフラッグ設置フラッグ設置
#define GAMEUI_HPP
#include <SFML/Graphics.hpp>
#include "Constants.hpp"

class GameUI{
    private:
    
        sf::Text leftInstructionText;//操作方法左クリックでマス開放
        sf::Text rightInstructionText;//操作方法右クリックでフラッグ設置
        sf::Text gameOverText;//ゲームオーバーテキストの表示
        sf::Text winText;//勝利時のテキスト
        sf::Text titleText;//タイトルのテキスト
        sf::Text pauseMenuText;//ポーズメニューのテキスト
        sf::RectangleShape goTitleButtonShape;//タイトルに戻るボタンの形
        sf::Text goTitleButtonText;//タイトルに戻るボタンのテキスト
        sf::RectangleShape menuButtonShape;//メニューボタンの形
        sf::Text menuButtonText;//メニューボタンのテキスト
        sf::RectangleShape continueButtonShape;//
        sf::Text continueButtonText;//
        sf::RectangleShape finishButtonShape;//
        sf::Text finishButtonText;//
        sf::RectangleShape easyButtonShape;//
        sf::Text easyButtonText;//
        sf::RectangleShape normalButtonShape;//
        sf::Text normalButtonText;//
        sf::RectangleShape hardButtonShape;//
        sf::Text hardButtonText;//
        sf::RectangleShape timeDisplayShape;//経過時間表示の枠
        sf::Text timeBoxText;//Timeって文字表示
        sf::Text timeDisplayText;//経過時間の表示
        sf::Clock gameClock;//タイマー使用時
        sf::Time totalElapsedTime;//合計の経過時間（この時間を表示）
        sf::Time elapsedTimeWhenPaused;//ポーズ時の経過時間

        int windowWidth;//
        int windowHeight;//
        int uiOffset;//UIエリアの高さ
        int nowSecond;//経過した時間
        float centerX;//
        float centerY;//

    public:
        GameUI(int windowWidth, int windowHeight, int offset);

    void updateLayout(int newWidth,int newHeight);//難易度変更時の盤面サイズ変更
    void startGameTimer();
    void pauseTimer();//ポーズ再開後の時間を保持（停止）するための関数
    void updateTimer(GameState currentState);//時間表示の関数
    void setFont(const sf::Font& loadedFont);//フォントを読み込み
    void Draw(sf::RenderWindow& window,GameState currentState) const;
    bool isGoTitleButtonClicked(const sf::Vector2i& mousePos) const;
    bool isMenuButtonClicked(const sf::Vector2i& mousePos) const;
    bool isContinueButtonClicked(const sf::Vector2i& mousePos) const;
    bool isFinishButtonClicked(const sf::Vector2i& mousePos) const;
    bool isEasyButtonClicked(const sf::Vector2i& mousePos) const;
    bool isNormalButtonClicked(const sf::Vector2i& mousePos) const;
    bool isHardButtonClicked(const sf::Vector2i& mousePos) const;
};

#endif