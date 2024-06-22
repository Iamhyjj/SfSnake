#include <SFML/Graphics.hpp>
#include <random>
#include <chrono>

#include "Fruit.h"

#include <random>

using namespace sfSnake;

const float Fruit::Radius = 5.f;

Fruit::Fruit(sf::Vector2f position)
{
	shape_.setPosition(position);
	shape_.setRadius(Fruit::Radius);
	switch(color_ = generateRandomColor()){
		case FruitColor::Black:
			shape_.setFillColor(sf::Color::Black);
			break;
		case FruitColor::Brown:
			shape_.setFillColor(sf::Color(96,56,17));
			break;
		case FruitColor::Blue:
			shape_.setFillColor(sf::Color::Blue);
			break;
		case FruitColor::Green:
			shape_.setFillColor(sf::Color::Green);
			break;
		case FruitColor::Red:
			shape_.setFillColor(sf::Color::Red);
			break;
	}
}


FruitColor Fruit::getColor() const{
	return color_;
}

FruitColor Fruit::generateRandomColor()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	static std::default_random_engine engine(seed);
	static std::uniform_real_distribution<float> distribution(0,1);
	float randomResult = distribution(engine);
	if(randomResult < 0.25){
		return randomResult < 0.125 ? FruitColor::Black : FruitColor::Brown;
	}
	if(randomResult < 0.5){
		return FruitColor::Red;
	}
	if(randomResult < 0.75){
		return FruitColor::Blue;
	}
	return FruitColor::Green;
}

void Fruit::render(sf::RenderWindow& window) const
{
	window.draw(shape_);
}

sf::FloatRect Fruit::getBounds() const
{
	return shape_.getGlobalBounds();
}

