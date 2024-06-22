#include <SFML/Graphics.hpp>

#include<iostream>
#include <memory>

#include "PauseScreen.h"
#include "MenuScreen.h"
#include "Game.h"
#include "GameScreen.h"
#include "Button.h"

using namespace sfSnake;

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 10.f);

std::shared_ptr<Screen> Game::Screen = std::make_shared<MenuScreen>();
std::shared_ptr<GameScreen> Game::GameScreen_ ;
std::shared_ptr<PauseScreen> Game::PauseScreen_;



Game::Game()
: window_(sf::VideoMode(Game::Width, Game::Height), "sfSnake")
{
	PauseScreen_ = std::make_shared<PauseScreen>();
    bgMusic_.openFromFile("Music/bg_music.wav");
	bgMusic_.setLoop(true);
	bgMusic_.play();
}

void Game::handleInput()
{
    sf::Event event;
    while (window_.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window_.close();
    }

    Game::Screen->handleInput(window_);
}

void Game::update(sf::Time delta)
{
	Game::Screen->update(delta);
}

void Game::render()
{
	window_.clear(Screen -> backgroundColor_);
	Game::Screen->render(window_);
	window_.display();
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (window_.isOpen())
	{
		sf::Time delta = clock.restart();
		timeSinceLastUpdate += delta;

		while (timeSinceLastUpdate > Game::TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			handleInput();
			update(TimePerFrame);
		}

		render();
	}
}