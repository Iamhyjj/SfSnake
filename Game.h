#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <memory>

#include "GameScreen.h"
#include "Screen.h"
#include "PauseScreen.h"
#include "Button.h"

namespace sfSnake
{
class Game
{
public:
	Game();

	void run();

	void handleInput();
	void update(sf::Time delta);
	void render();

	static const int Width = 1000;
	static const int Height = 960;

	static std::shared_ptr<Screen> Screen;
	static std::shared_ptr<GameScreen> GameScreen_;
	static std::shared_ptr<PauseScreen> PauseScreen_;

private:
	sf::RenderWindow window_;
	sf::Music bgMusic_;
	
	static const sf::Time TimePerFrame;
};
}


#endif