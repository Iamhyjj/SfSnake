#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "SnakeNode.h"
#include <cmath>

using namespace sfSnake;

const float SnakeNode::NodeRadius_ = 10.0f;
const sf::Texture SnakeNode::headTexture_ = []() {
    sf::Texture texture;
    if (!texture.loadFromFile("Texture/SnakeHead.png")) {
        std::cerr << "Failed to load texture from file SnakeHead.png\n";
    }
    return texture;
}();

const sf::Texture SnakeNode::bodyTexture_ = []() {
    sf::Texture texture;
    if (!texture.loadFromFile("Texture/SnakeBody.png")) {
        std::cerr << "Failed to load texture from file SnakeBody.png\n";
    }
    return texture;
}();

const sf::Texture SnakeNode::shieldedHeadTexture_ = []() {
    sf::Texture texture;
    if (!texture.loadFromFile("Texture/ShieldedSnakeHead.png")) {
        std::cerr << "Failed to load texture from file ShieldedSnakeHead.png\n";
    }
    return texture;
}();

SnakeNode::SnakeNode(sf::Vector2f position) : position_(position) , angle_(0)
{
	sprite_.setPosition(position_);
}

SnakeHead::SnakeHead(sf::Vector2f& position): SnakeNode(position)
{
	sprite_.setTexture(headTexture_);
	sprite_.setOrigin(headTexture_.getSize().x / 2 , headTexture_.getSize().y / 2);
	sprite_.setScale(0.18,0.225);
}


SnakeBody::SnakeBody(sf::Vector2f& position): SnakeNode(position)
{
	sprite_.setTexture(bodyTexture_);
	sprite_.setOrigin(bodyTexture_.getSize().x / 2 , bodyTexture_.getSize().y / 2);
	sprite_.setScale(0.06,0.06);
}

void SnakeHead::setShieldedTexture(bool shieleded){
	if(shieleded){
		sprite_.setTexture(shieldedHeadTexture_);
	}
	else{
		sprite_.setTexture(headTexture_);
	}
}


void SnakeNode::rotate(float angle)
{
	sprite_.rotate(angle); 
}


void SnakeNode::setPosition(sf::Vector2f position)
{
	position_ = position;
	sprite_.setPosition(position_);
}

void SnakeNode::setPosition(float x, float y)
{
	position_.x = x;
	position_.y = y;
	sprite_.setPosition(position_);
}

float SnakeNode::getRotation() const
{
	return sprite_.getRotation();
}



void SnakeNode::move(float xOffset, float yOffset)
{
	position_.x += xOffset;
	position_.y += yOffset;
	float new_angle = atan2(yOffset,xOffset) + M_PI_2;
	float delta_angle = (180/M_PI)*new_angle - sprite_.getRotation();
	sprite_.rotate(delta_angle);
	sprite_.move(xOffset, yOffset);
	angle_ = sprite_.getRotation();
}

sf::FloatRect SnakeNode::getBounds() const
{
	return sprite_.getGlobalBounds();
}

sf::Vector2f SnakeNode::getPosition() const
{
	return sprite_.getPosition();
}

void SnakeNode::render(sf::RenderWindow& window)
{
	window.draw(sprite_);
}