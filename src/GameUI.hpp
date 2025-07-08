#ifndef GAMEUI_HPP
#define GAMEUI_HPP
#include <SFML/Graphics.hpp>
#include "Constants.hpp"

class GameUI {
    private:
        // sf::Font &Font; // setFontで後から設定
        sf::Text leftInstructionText;
        sf::Text rightInstructionText;
        sf::Text gameOverText;
        sf::Text winText;
        sf::Text titleText;
        sf::Text pauseMenuText;
        sf::RectangleShape goTitleButtonShape;
        sf::Text goTitleButtonText;
        sf::RectangleShape menuButtonShape;
        sf::Text menuButtonText;
        sf::RectangleShape continueButtonShape;
        sf::Text continueButtonText;
        sf::RectangleShape finishButtonShape;
        sf::Text finishButtonText;
        sf::RectangleShape easyButtonShape;
        sf::Text easyButtonText;
        sf::RectangleShape normalButtonShape;
        sf::Text normalButtonText;
        sf::RectangleShape hardButtonShape;
        sf::Text hardButtonText;
        int windowWidth;
        int windowHeight;
        int uiOffset;
        float centerX;
        float centerY;


    public:
        GameUI(int windowWidth, int windowHeight, int offset);

    void updateLayout(int newWidth,int newHeight);
    void setFont(const sf::Font& loadedFont);
    void Draw(sf::RenderWindow& window, GameState currentState) const;
    bool isGoTitleButtonClicked(const sf::Vector2i& mousePos) const;
    bool isMenuButtonClicked(const sf::Vector2i& mousePos) const;
    bool isContinueButtonClicked(const sf::Vector2i& mousePos) const;
    bool isFinishButtonClicked(const sf::Vector2i& mousePos) const;
    bool isEasyButtonClicked(const sf::Vector2i& mousePos) const;
    bool isNormalButtonClicked(const sf::Vector2i& mousePos) const;
    bool isHardButtonClicked(const sf::Vector2i& mousePos) const;
};

#endif