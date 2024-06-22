#include <SFML/Graphics.hpp>

#include <random>
#include <memory>
#include<iostream>

#include "Obstacle.h"
#include "GameScreen.h"
#include "GameOverScreen.h"
#include "Game.h"
#include "PauseScreen.h"

using namespace sfSnake;

bool GameScreen::showGrid_ = 1;
int GameScreen::initCnt = 0;

GameScreen::GameScreen() : snake_(),shieldedTime_(sf::seconds(0)),fruitNum(10),obsNum(3),itemNum(1),timeLimit_(100),itemTimeLimit(7),itemInterval(25),shieldTimeLimit(15)
{
	initLines();
	font_.loadFromFile("Fonts/game_over.ttf");
	timer_.setFont(font_);
	scoreText_.setFont(font_);
	scoreText_.setString("Score: 0");
	scoreText_.setString("Time: " + std::to_string(timeLimit_));
	scoreText_.setCharacterSize(24);
	timer_.setCharacterSize(24);
	scoreText_.setFillColor(sf::Color::Green);
	timer_.setFillColor(sf::Color::Green);
	scoreText_.setPosition(Game::Width - 200 , 20);
	timer_.setPosition(Game::Width-200,60);
	engine_.seed(static_cast<unsigned int>(time(NULL)));
	generateObstacle();
	if(initCnt==0){
		initCnt++;
		showGrid_=1;
	}
	fruitClock_.restart();
	gameClock_.restart();
	itemIntervalClock_.restart();
}

void GameScreen::initLines()
{
	const int gridSize = 20; // 网格尺寸
	
	for (int x = 0; x < Game::Width; x += gridSize) {
		sf::RectangleShape line(sf::Vector2f(1, Game::Height));
		line.setFillColor(sf::Color(200, 200, 200));
		line.setPosition(x, 0);
		lines_.push_back(line);
	}

	for (int y = 0; y < Game::Height; y += gridSize) {
		sf::RectangleShape line(sf::Vector2f(Game::Width, 1));
		line.setFillColor(sf::Color(200, 200, 200));
		line.setPosition(0, y);
		lines_.push_back(line);
	}
}


void GameScreen::switchShowGrid(){
	showGrid_ = !showGrid_;
}

void GameScreen::addTimeLimit(float time)
{
	timeLimit_ += time;
}

void GameScreen::handleInput(sf::RenderWindow& window)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)&&Game::PauseScreen_->readClock().asMilliseconds()>=200){
		Game::Screen = Game::PauseScreen_;
		Game::PauseScreen_->resetInputClock();
		Game::PauseScreen_->resetPauseClock();
	} //防抖防止按esc过快
	snake_.handleInput(window);
}


void GameScreen::updateTimer()
{
	timer_.setString("Time: "+std::to_string(int(timeLimit_-gameClock_.getElapsedTime().asSeconds())));
}

void GameScreen::updateScore()
{
	scoreText_.setString("Score: " + std::to_string(snake_.getSize()+snake_.getBounsScore_()));
}

void GameScreen::update(sf::Time delta)
{
	if ((fruit_.size() < fruitNum && fruitClock_.getElapsedTime().asSeconds()>=5 )||(fruit_.size()==0)){
		generateFruit();
		fruitClock_.restart();
	}

	if(items_.size() == 0 && itemIntervalClock_.getElapsedTime().asSeconds() >= itemInterval){
		generateItems();
		itemClock_.restart();
		itemIntervalClock_.restart();
	}
	else if(itemClock_.getElapsedTime().asSeconds() >= itemTimeLimit && !items_.empty()){
		items_.clear();
	}

	for(auto& obs:obstacles_){
		obs.rotate();
	}

	snake_.update(delta);
	snake_.checkFruitCollisions(fruit_);
	snake_.checkObstacleCollisions(obstacles_);
	snake_.checkItemColiisions(items_);
	handleItemEffects(delta); 
	updateScore();
	updateTimer();

	if (snake_.dead() || gameClock_.getElapsedTime().asSeconds() >= timeLimit_){
		Game::Screen = std::make_shared<GameOverScreen>(snake_.getSize()+snake_.getBounsScore_());
	}
}

void GameScreen::handleItemEffects(sf::Time delta)
{
	if(snake_.isShielded()&&shieldedTime_ == sf::seconds(0)){
		shieldedTime_ += sf::seconds(shieldTimeLimit);
	}
	if(shieldedTime_>=sf::seconds(0)){
		shieldedTime_ -= delta;
		if(shieldedTime_ <= sf::seconds(0)){
			snake_.setShielded(false);
			shieldedTime_ = sf::seconds(0);
		}
	}

}


void GameScreen::render(sf::RenderWindow& window) const
{
	//蛇在护盾即将消失时会闪烁
	if(snake_.isShielded() && shieldedTime_ < sf::seconds(1)){
        float time = gameClock_.getElapsedTime().asSeconds();
        bool showSnake = (std::fmod(time, 0.3f) < 0.15f);
        if(showSnake){
            snake_.render(window);
        }
    }
    else{
        snake_.render(window);
    }
	
	if(showGrid_){
		renderGrid(window);
	}

	for (const auto& fruit : fruit_){
		fruit.render(window);
	}

	for(const auto& obs : obstacles_){
		obs.render(window);
	}

	//物品即将消失时会闪烁
	for(const auto& item:items_){
        if(itemClock_.getElapsedTime() >= sf::seconds(itemTimeLimit)-sf::seconds(1.5)){
            float time = gameClock_.getElapsedTime().asSeconds();
        	bool showItem = (std::fmod(time, 0.3f) < 0.15f);
			if(showItem){
				item->render(window);
			}
        } 
		else{
			item->render(window);
		}
	}

	window.draw(scoreText_);
	window.draw(timer_);

}

void GameScreen::renderGrid(sf::RenderWindow& window) const
{
	for(const auto& line:lines_){
		window.draw(line);
	}
}

void GameScreen::generateFruit()
{
	bool positionValid;
	sf::Vector2f fruitPosition;
	static std::uniform_real_distribution<float> xDistribution(2*Fruit::Radius,Game::Width - 2*Fruit::Radius);
	static std::uniform_real_distribution<float> yDistribution(2*Fruit::Radius, Game::Height - 2*Fruit::Radius);
	//生成的水果不能与已生成的水果、障碍和蛇过近
	for(auto i{fruit_.size()} ; i < fruitNum; ++i){
		do{
			positionValid = 1;
			fruitPosition = sf::Vector2f{xDistribution(engine_),yDistribution(engine_)};
			sf::CircleShape tmp(Fruit::Radius);
			tmp.setPosition(fruitPosition);
			for(const auto& node: snake_.getNodes()){
				if(node -> getBounds().intersects(tmp.getGlobalBounds())){
					positionValid = 0;
					break;
				}
			}
			for(const auto& obs:obstacles_){
				if(tmp.getGlobalBounds().intersects(obs.getBounds())){
					positionValid = 0;
					break;
				}
			}
		}while(!positionValid);
		fruit_.emplace_back(Fruit(fruitPosition));
	}
}

void GameScreen::generateObstacle()
{
	bool positionValid;
	sf::Vector2f obsPosition;
	static std::uniform_real_distribution<float> xDistribution(100,Game::Width - 100);
	static std::uniform_real_distribution<float> yDistribution(100, Game::Height - 100);
	//生成的障碍不会与已生成的水果、障碍和蛇过近
	for(auto i{obstacles_.size()} ; i < obsNum; ++i){
		do{
			positionValid = 1;
			obsPosition = sf::Vector2f{xDistribution(engine_),yDistribution(engine_)};
			//生成的障碍不应和蛇节点重合
			for(const auto& node: snake_.getNodes()){
				if(node -> getBounds().intersects(Obstacle(obsPosition).getBounds())){
					positionValid = 0;
					break;
				}
			}
			//生成的障碍不应距离水果太近
			for(const auto& fruit:fruit_){
				if(fruit.getBounds().intersects(Obstacle(obsPosition).getBounds())){
					positionValid = 0;
					break;
				}
			}
			//生成的障碍不能和已生成的障碍太近
			for(const auto& obs:obstacles_){
				if(obs.getBounds().intersects(Obstacle(obsPosition).getBounds())){
					positionValid = 0;
					break;

				}
			}
		}while(!positionValid);
		obstacles_.emplace_back(Obstacle(obsPosition));	
	}
}

void GameScreen::generateItems()
{
	bool positionValid;
	sf::Vector2f itemPosition;
	std::shared_ptr<Item> p;
	static std::uniform_real_distribution<float> xDistribution(100,Game::Width - 100);
	static std::uniform_real_distribution<float> yDistribution(100, Game::Height - 100);
	static std::uniform_int_distribution<> itemDistribution(0,Item::itemTypeNum-1);
	//生成的物品不会与已生成的障碍、水果、蛇过近
	for(auto i{items_.size()} ; i < itemNum; ++i){
		do{
			positionValid = 1;
			itemPosition = sf::Vector2f{xDistribution(engine_),yDistribution(engine_)};
			//随机生成一种道具
			switch(itemDistribution(engine_)){
				case(0):
					p = std::make_shared<Shield>(itemPosition);
					break;
				case(1):
					p = std::make_shared<Bonus>(itemPosition);
					break;
				case(2):
					p = std::make_shared<Clock>(itemPosition);
					break;
			}
			for(const auto& node: snake_.getNodes()){
				if(node -> getBounds().intersects(p->getBounds())){
					positionValid = 0;
					break;
				}
			}
			for(const auto& fruit:fruit_){
				if(fruit.getBounds().intersects((p->getBounds()))){
					positionValid = 0;
					break;
				}
			}

			for(const auto& obs:obstacles_){
				if(obs.getBounds().intersects(p->getBounds())){
					positionValid = 0;
					break;
				}
			}
		}while(!positionValid);
		items_.push_back(p);
	}
}
