#ifndef FRUIT_H
#define FRUIT_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
enum class FruitColor{
	Black,
	Green,
	Brown,
	Red,
	Blue
};

class Fruit
{
public:
	Fruit(sf::Vector2f position = sf::Vector2f(0, 0));

	FruitColor getColor() const;


	void render(sf::RenderWindow& window) const;

	FruitColor generateRandomColor();

	sf::FloatRect getBounds() const;

	static const float Radius;
private:
	sf::CircleShape shape_;

	FruitColor color_;

	

};

} //namespace sfSnake

#endif