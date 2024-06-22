#include <iostream>

#include "Obstacle.h"

#include <SFML/Graphics.hpp>

const float Obstacle::Radius = 45.f;

const sf::Texture Obstacle::obsTexture_ = []() {
    sf::Texture texture;
    if (!texture.loadFromFile("Texture/Obstacle.png")) {
        std::cerr << "Failed to load texture from file texture_path.png\n";
    }
    return texture;
}();

Obstacle::Obstacle(sf::Vector2f& position) : angularVelocity_(10)
{
    obsSrite_.setTexture(obsTexture_);
    obsSrite_.setScale(0.25,0.25);
    obsSrite_.setOrigin(obsTexture_.getSize().x/2 , obsTexture_.getSize().y/2);
    obsSrite_.setPosition(position);
}

void Obstacle::rotate()
{
    obsSrite_.rotate(angularVelocity_);
}

void Obstacle::render(sf::RenderWindow& window) const
{
    window.draw(obsSrite_);
}

sf::FloatRect Obstacle::getBounds() const
{
    return obsSrite_.getGlobalBounds();
}

sf::Vector2f Obstacle::getPostion() const
{
    return obsSrite_.getPosition();
}

