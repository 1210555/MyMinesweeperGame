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
        sf::RectangleShape restartButtonShape;
        sf::Text restartButtonText;
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
        sf::RectangleShape difficultButtonShape;
        sf::Text difficultButtonText;
        int windowWidth;
        int windowHeight;
        int uiOffset;

    public:
        GameUI(int windowWidth, int windowHeight, int offset);

    void setFont(const sf::Font& loadedFont);
    void Draw(sf::RenderWindow& window, GameState currentState) const;
    bool isRestartButtonClicked(const sf::Vector2i& mousePos) const;
    bool isMenuButtonClicked(const sf::Vector2i& mousePos) const;
    bool isContinueButtonClicked(const sf::Vector2i& mousePos) const;
    bool isFinishButtonClicked(const sf::Vector2i& mousePos) const;
    bool isEasyButtonClicked(const sf::Vector2i& mousePos) const;
    bool isNormalButtonClicked(const sf::Vector2i& mousePos) const;
    bool isDifficultButtonClicked(const sf::Vector2i& mousePos) const;
};

#endif