#ifndef SNAKE_H
#define SNAKE_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <memory>
#include <vector>

#include "Item.h"
#include "Obstacle.h"
#include "SnakeNode.h"
#include "Fruit.h"

namespace sfSnake
{

class Snake
{
public:
	Snake();
	std::vector<std::shared_ptr<SnakeNode>> getNodes() const;
	void handleInput(sf::RenderWindow&);
	void update(sf::Time delta);
	void render(sf::RenderWindow& window) const;
	void checkFruitCollisions(std::vector<Fruit>& fruits);
	void checkObstacleCollisions(std::vector<Obstacle>&);
	void checkItemColiisions(std::vector<std::shared_ptr<Item>>&);
	void setShielded(bool);
	bool dead() const;
	bool isShielded() const;
	int getBounsScore_() const;
	unsigned getSize() const;

private:
	void move();
	void grow(unsigned short length = 1);
	void checkEdgeCollisions();
	void checkSelfCollisions();
	void initNodes();
	void setDirectionVector(sf::Vector2f&);
	int  bonusScore_;
	bool dead_;
	bool shielded_;

	sf::Vector2f position_;

	sf::Vector2f directionVector_;          


	sf::SoundBuffer pickupBuffer_;
	sf::Sound pickupSound_;

	sf::SoundBuffer dieBuffer_;
	sf::Sound dieSound_;

	std::vector<std::shared_ptr<SnakeNode>> nodes_;
	static const int InitialSize;
};
}

#endif