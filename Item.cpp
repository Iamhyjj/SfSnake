#include <iostream>
#include <memory>

#include "Item.h"


#include <SFML/Graphics.hpp>

const int Item::itemTypeNum = 3;

const sf::Texture Shield::shieldTexture_ = []() {
    sf::Texture texture;
    if (!texture.loadFromFile("Texture/Shield.png")) {
        std::cerr << "Failed to load texture from file Texture/Shield.png.png\n";
    }
    return texture;
}();

const sf::Texture Clock::clockTexture_ = []() {
    sf::Texture texture;
    if (!texture.loadFromFile("Texture/Clock.png")) {
        std::cerr << "Failed to load texture from file Texture/Clock.png\n";
    }
    return texture;
}();

const sf::Texture Bonus::bonusTexture_ = []() {
    sf::Texture texture;
    if (!texture.loadFromFile("Texture/Bonus.png")) {
        std::cerr << "Failed to load texture from file Texture/Bonus.png\n";
    }
    return texture;
}();

sf::FloatRect Item::getBounds() const
{
    return itemSprite_.getGlobalBounds();
}

void Item::render(sf::RenderWindow& window) const
{
    window.draw(itemSprite_);
}

Item::Item(sf::Vector2f& position)
{
    itemSprite_.setPosition(position);
}

Shield::Shield(sf::Vector2f& position) : Item(position)
{
    itemSprite_.setTexture(shieldTexture_);
    itemSprite_.setScale(0.2,0.2);
}

Bonus::Bonus(sf::Vector2f& position) : Item(position)
{
    itemSprite_.setTexture(bonusTexture_);
    itemSprite_.setScale(0.2,0.2);
}

Clock::Clock(sf::Vector2f& position) : Item(position)
{
    itemSprite_.setTexture(clockTexture_);
    itemSprite_.setScale(0.2,0.2);
}
