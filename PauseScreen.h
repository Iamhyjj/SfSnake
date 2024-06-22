#ifndef PAUSE_H
#define PAUSE_H

#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "Button.h"

namespace sfSnake
{
class PauseScreen : public Screen
{
    public:
        PauseScreen();
        void handleInput(sf::RenderWindow& window) override;
        void update(sf::Time delta) override;
        void render(sf::RenderWindow& window) const override;
        void resetInputClock();
        void resetPauseClock();
        sf::Time readClock() const;

    private:
        sf::Clock inputClock_; //为了防抖加入的时钟
        sf::Clock pauseClock_; //计算在暂停屏幕停留了多久
        const sf::Time inputDelay = sf::milliseconds(200);
        sf::Font font_;
        sf::Text title_;
        sf::Text showGridText_;
        sf::Text backgroundColorText_;
        ShowGridButton gridButton_;
        BackgroundColorButton backgroundButton_;
};
}

#endif