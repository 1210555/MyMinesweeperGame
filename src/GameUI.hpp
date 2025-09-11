#ifndef GAMEUI_HPPフラッグ設置フラッグ設置
#define GAMEUI_HPP
#include <SFML/Graphics.hpp>
#include "Constants.hpp"

class GameUI{
    private:
    
        sf::Text leftInstructionText;//操作方法左クリックでマス開放
        sf::Text rightInstructionText;//操作方法右クリックでフラッグ設置
        sf::Text gameOverText;//ゲームオーバーテキストの表示
        sf::RectangleShape endGamePanelShape;//winテキストをいれるボックス
        sf::Text winText;//勝利時のテキスト
        sf::Text titleText;//タイトルのテキスト
        sf::Text pauseMenuText;//ポーズメニューのテキスト
        sf::RectangleShape pauseMenuPanelShape;//ポーズメニューのボックス
        sf::RectangleShape goTitleButtonShape;//タイトルに戻るボタンの形
        sf::Text goTitleButtonText;//タイトルに戻るボタンのテキスト
        sf::RectangleShape menuButtonShape;//メニューボタンの形
        sf::Text menuButtonText;//メニューボタンのテキスト
        sf::RectangleShape continueButtonShape;//
        sf::Text continueButtonText;//
        sf::RectangleShape finishButtonShape;//
        sf::Text finishButtonText;//
        //sf::ConvexShape easyButtonShape;
        sf::ConvexShape easyButtonShape;//
        sf::Text easyButtonText;//
        sf::ConvexShape normalButtonShape;//
        sf::Text normalButtonText;//
        sf::ConvexShape hardButtonShape;//
        sf::Text hardButtonText;//
        sf::RectangleShape timeDisplayShape;//経過時間表示の枠
        sf::Text timeBoxText;//Timeって文字表示
        sf::Text timeDisplayText;//経過時間の表示
        sf::Clock gameClock;//タイマー使用時
        sf::Time totalElapsedTime;//合計の経過時間（この時間を表示）
        sf::Time elapsedTimeWhenPaused;//ポーズ時の経過時間
        sf::RectangleShape visualGuidance_glayLine;//メインメニューのグレーのライン
        sf::RectangleShape visualGuidance_blackLine;
<<<<<<< HEAD
        sf::Text m_reverseColorTitleText;
        sf::Text m_reverseColorEasyText;
        sf::Text m_reverseColorNormalText;
        sf::Text m_reverseColorHardText;
        sf::ConvexShape m_reverseColorEasyButtonShape;//
        sf::ConvexShape m_reverseColorNormalButtonShape;//
        sf::ConvexShape m_reverseColorHardButtonShape;//
=======
>>>>>>> 5e26d58a6f2db4286d41943a1673e86009ae03ab


        mutable sf::Shader m_clipperShader;//シェーダーオブジェクト
        mutable sf::Shader m_shapeClipperShader;
//mutable:const関数内でもこれがついていれば値の変更ができるようになる。
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
    void setMainFont(const sf::Font& loadedMainFont);//メインメニューのフォント
    void initializeStyles();
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