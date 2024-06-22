#include <SFML/Graphics.hpp>

#include "PauseScreen.h"
#include "Button.h"
#include "Game.h"
#include "GameScreen.h"
#include "Screen.h"

using namespace sfSnake;


sf::Color Screen::backgroundColor_ = sf::Color::White;
PauseScreen::PauseScreen()
{	
    font_.loadFromFile("Fonts/game_over.ttf");
    float lineSpace = 60.0f;
    //set title text
	title_.setFont(font_);
    title_.setCharacterSize(40);
    title_.setFillColor(sf::Color::Green);
    title_.setString("Game Options");
    sf::FloatRect titleBounds = title_.getLocalBounds();
    title_.setOrigin(titleBounds.left + titleBounds.width / 2.0f, titleBounds.top);
    title_.setPosition(Game::Width / 2.0f, 0);
   
    //set option text
    showGridText_.setFont(font_);
    showGridText_.setCharacterSize(30);
    showGridText_.setFillColor(sf::Color::Green);
    sf::FloatRect gridTextBounds = showGridText_.getGlobalBounds();
    showGridText_.setOrigin(gridTextBounds.left , gridTextBounds.top);
    showGridText_.setPosition(Game::Width / 8 , titleBounds.height + lineSpace);
    showGridText_.setString("Show Grid");

    backgroundColorText_.setFont(font_);
    backgroundColorText_.setCharacterSize(30);
    backgroundColorText_.setFillColor(sf::Color::Green);
    sf::FloatRect backgroundTextBounds = backgroundColorText_.getGlobalBounds();
    backgroundColorText_.setOrigin(backgroundTextBounds.left , backgroundTextBounds.top);
    backgroundColorText_.setPosition(Game::Width / 8 , gridTextBounds.height + titleBounds.height + 3.5 * lineSpace);
    backgroundColorText_.setString("Background Color");
    
    //set buttons
    sf::Vector2f btPosition;
    btPosition.x = Game::Width - ShowGridButton::width * 2;
    btPosition.y = showGridText_.getPosition().y;
    gridButton_.setPosition(btPosition);
    gridButton_.setText("On");

    btPosition.y = backgroundColorText_.getPosition().y;
    backgroundButton_.setPosition(btPosition);
    backgroundButton_.setText("White");

}

void PauseScreen::resetPauseClock()
{
    pauseClock_.restart();
}

void PauseScreen::resetInputClock()
{
    inputClock_.restart();
}

sf::Time PauseScreen::readClock() const
{
    return inputClock_.getElapsedTime();
}

void PauseScreen::handleInput(sf::RenderWindow& window) {
    if (inputClock_.getElapsedTime() < inputDelay)
        return; // 如果自上次输入以来还没有过去足够的延迟时间，则不处理此次输入

    // 是键盘的escape键处理
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        Game::GameScreen_->addTimeLimit(pauseClock_.getElapsedTime().asSeconds());
        Game::Screen = Game::GameScreen_;
        inputClock_.restart(); // 重置时钟
    }

    // 是鼠标左键的处理
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosFloat = window.mapPixelToCoords(mousePosition);

        // 获取按钮的全局边界来检查鼠标点击是否落在相应的按钮上
        sf::FloatRect gridBounds = gridButton_.getBounds();
        sf::FloatRect backgroundBounds = backgroundButton_.getBounds();

        if (gridBounds.contains(mousePosFloat)) {
            gridButton_.activate(window);
            inputClock_.restart(); // 一旦有效的输入发生，重置输入时钟

        } 
        else if (backgroundBounds.contains(mousePosFloat)) {
            backgroundButton_.activate(window);
            Screen::backgroundColor_ = backgroundButton_.getBackgroundColor();
            inputClock_.restart(); // 重置时钟
        }
    }
}


void PauseScreen::update(sf::Time delta)
{
    
}

void PauseScreen::render(sf::RenderWindow& window) const
{
    window.draw(title_);
    window.draw(showGridText_);
    window.draw(backgroundColorText_);
    gridButton_.render(window);
    backgroundButton_.render(window);
}