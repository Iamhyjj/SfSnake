#include <iostream>
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "GameScreen.h"
using namespace sfSnake;

const float Button::width = 80;
const float Button::height = 40;

void Button::setPosition(const sf::Vector2f& position)
{
    shape_.setPosition(position);
}

sf::FloatRect Button::getBounds() const
{
    return shape_.getGlobalBounds();
}


Button::Button()
{
    font_.loadFromFile("Fonts/game_over.ttf");
    text_.setFont(font_);
    text_.setCharacterSize(24);
    text_.setFillColor(sf::Color::Green);
    shape_.setSize({width,height});
    shape_.setFillColor(sf::Color(192,192,192));
}

ShowGridButton::ShowGridButton() : Button() , showGrid_(1)
{
    
}

BackgroundColorButton::BackgroundColorButton() : Button() , backgroundColor_(sf::Color::White)
{
    text_.setCharacterSize(20);
}

void Button::render(sf::RenderWindow& window) const
{
    window.draw(shape_);
    window.draw(text_);
}

void Button::setText(const sf::String& newText) {
    text_.setString(newText); // 更新文本内容

    // 重新计算并设置文本的原点，用于居中文本
    sf::FloatRect textBounds = text_.getLocalBounds();
    text_.setOrigin(textBounds.left + textBounds.width / 2.0f,
                    textBounds.top + textBounds.height / 2.0f);

    // 计算矩形的中心位置
    sf::FloatRect shapeBounds = shape_.getGlobalBounds();
    float shapeCenterX = shapeBounds.left + shapeBounds.width / 2.0f;
    float shapeCenterY = shapeBounds.top + shapeBounds.height / 2.0f;

    // 将文本移动到矩形中心
    text_.setPosition(shapeCenterX, shapeCenterY);
}

void ShowGridButton::activate(sf::RenderWindow& window)
{
    if(showGrid_){
        setText("Off");
        text_.setFillColor(sf::Color::Red);
        GameScreen::switchShowGrid();
        
    }
    else{
        setText("On");
        text_.setFillColor(sf::Color::Green);
        GameScreen::switchShowGrid();
    }
    // 切换显示网格的状态
    showGrid_ = !showGrid_;
}

void BackgroundColorButton::activate(sf::RenderWindow& window)
{
    if(backgroundColor_ == sf::Color::White){
        setText("Black");
        backgroundColor_ = sf::Color::Black;
    }
    else if(backgroundColor_ == sf::Color::Black){
        setText("Brown");
        backgroundColor_ = sf::Color(96,56,17);
    }
    else{
        setText("White");
        backgroundColor_ = sf::Color::White;
    } 
    
}

sf::Color BackgroundColorButton::getBackgroundColor() const{
    return backgroundColor_;
}
