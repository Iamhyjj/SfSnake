#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include <memory>
#include <random>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "Item.h"
#include "Obstacle.h"
#include "Screen.h"
#include "Snake.h"
#include "Fruit.h"

namespace sfSnake
{
class GameScreen : public Screen
{
public:
	GameScreen();
	void addTimeLimit(float);
	void handleInput(sf::RenderWindow& window) override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) const override;
	void renderGrid(sf::RenderWindow&) const;
	void updateScore();
	void updateTimer();
	void generateFruit();
	void generateObstacle();
	void generateItems();
	void setInvincible();
	void initLines();
	void handleItemEffects(sf::Time delta);
	static void switchShowGrid();
	const unsigned short fruitNum;
	const unsigned short obsNum;
	const unsigned short itemNum;
	const float itemTimeLimit;
	const float itemInterval;
	const float shieldTimeLimit;
	sf::Sprite sprite_;
	sf::Texture texture_;

private:
	Snake snake_;
	std::default_random_engine engine_; //用于随机生成随机数的引擎
	std::vector<Fruit> fruit_;
	std::vector<Obstacle> obstacles_;
	std::vector<std::shared_ptr<Item>> items_;
	std::vector<sf::RectangleShape> lines_; //用于绘制格子的线
	sf::Font font_;
	sf::Text scoreText_;
	sf::Text timer_;
	sf::RectangleShape line;
	sf::Color gridColor_;
	static bool showGrid_;
	static int initCnt;
	float timeLimit_;
	sf::Clock fruitClock_;
	sf::Clock itemClock_;
	sf::Clock itemIntervalClock_;
	sf::Clock gameClock_;
	sf::Time shieldedTime_;

};
}

#endif