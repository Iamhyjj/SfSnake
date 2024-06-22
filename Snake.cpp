#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>
#include <cmath>

#include "Snake.h"
#include "Game.h"
#include "Fruit.h"
#include "SnakeNode.h"
#include "GameOverScreen.h"


using namespace sfSnake;

const int Snake::InitialSize = 5;


Snake::Snake() : directionVector_(0,-1),dead_(false),shielded_(false),bonusScore_(0)
{
	initNodes();
	pickupBuffer_.loadFromFile("Sounds/pickup.aiff");
	pickupSound_.setBuffer(pickupBuffer_);
	pickupSound_.setVolume(30);
	dieBuffer_.loadFromFile("Sounds/die.wav");
	dieSound_.setBuffer(dieBuffer_);
	dieSound_.setVolume(50);
}

std::vector<std::shared_ptr<SnakeNode>> Snake::getNodes() const{
	return nodes_;
}

void Snake::initNodes()
{
    sf::Vector2f tempPos {Game::Width / 2 , Game::Height / 2};
	std::shared_ptr<SnakeNode> p = std::make_shared<SnakeHead>(tempPos);
	nodes_.push_back(p);
	nodes_[0]->setPosition(tempPos);
	for (int i = 1; i < Snake::InitialSize; ++i)
    {
        tempPos.y += i*SnakeNode::NodeRadius_;
		p = std::make_shared<SnakeBody>(tempPos);
		nodes_.push_back(p);
    }
}

void Snake::handleInput(sf::RenderWindow& window)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        // 获得鼠标点击位置
        sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        // 获得蛇头位置
        sf::Vector2f snakeHeadPosition = nodes_[0]->getPosition();
        // 计算方向向量
        sf::Vector2f direction = mousePosition - snakeHeadPosition;
        // 使用这个方向向量设定新的方向
		setDirectionVector(direction);
    }
}

void Snake::update(sf::Time delta)
{
	checkEdgeCollisions();
	move();
	if(!shielded_){
		checkSelfCollisions();
	}
}

void Snake::checkFruitCollisions(std::vector<Fruit>& fruits)
{
	decltype(fruits.begin()) toRemove = fruits.end();

	for (auto it = fruits.begin(); it != fruits.end(); ++it)
	{
		if (it->getBounds().intersects(nodes_[0]->getBounds())){
			toRemove = it;
			break;
		}
	}

	if (toRemove != fruits.end())
	{
		pickupSound_.play();
		switch (toRemove->getColor())
		{
		case FruitColor::Black:
			break;
		case FruitColor::Brown:
			break;
		case FruitColor::Green:
			grow();
			break;
		case FruitColor::Blue:
			grow(2);
			break;
		case FruitColor::Red:
			grow(3);
			break;
		default:
			break;
		}
		fruits.erase(toRemove);
	}
}

void Snake::setShielded(bool shielded)
{
	shielded_ = shielded;
	if(!shielded_){
		nodes_[0]->setShieldedTexture(false);
	}
	else{
		nodes_[0]->setShieldedTexture(true);
	}
}

void Snake::grow(unsigned short length)
{
	float diameter = 2 * nodes_[0] -> NodeRadius_;
	std::shared_ptr<SnakeNode> p;
	for(auto i{0};i<length;i++){
	sf::Vector2f pos {nodes_[nodes_.size() - 1]->getPosition().x + directionVector_.x * diameter,
	 			nodes_[nodes_.size() - 1]->getPosition().y + directionVector_.y*diameter};
	p= std::make_shared<SnakeBody>(pos);
	nodes_.push_back(p);
	}
}

unsigned Snake::getSize() const
{
	return nodes_.size();
}

int Snake::getBounsScore_() const
{
	return bonusScore_;
}

bool Snake::dead() const
{
	return dead_;
}

bool Snake::isShielded() const
{
	return shielded_;
}

bool circlesIntersect(const sf::Vector2f& position1, float radius1, const sf::Vector2f& position2, float radius2) {
    float dx = position1.x - position2.x;
    float dy = position1.y - position2.y;
    float distance = std::sqrt(dx * dx + dy * dy);
	float relaxationFactor = 0.8;  //严格的圆形判定可能过于严苛，这里使用宽松系数调整判定条件
	return distance < (radius1 + radius2) * relaxationFactor;
}

void Snake::checkSelfCollisions() {
    const auto& headNode = nodes_[0];
    const float headRadius = headNode->NodeRadius_; 
    const sf::Vector2f headPosition = headNode->getPosition(); 

    for (decltype(nodes_.size()) i = 3; i < nodes_.size(); ++i) {     //忽略蛇头与第二、三个节点的碰撞判定
        if (circlesIntersect(headPosition, headRadius, nodes_[i]->getPosition(), nodes_[i]->NodeRadius_)) {
			dieSound_.play();
            sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
            dead_ = true;  
			break;
        }
    }
}

void Snake::checkObstacleCollisions(std::vector<Obstacle>& obstacles)
{
	if(!shielded_){
		for(const auto& obs : obstacles){
			if(circlesIntersect(obs.getPostion(),Obstacle::Radius,nodes_[0]->getPosition(),nodes_[0]->NodeRadius_)){
				dieSound_.play();
				sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
				dead_ = true;
				break;
			}
		}
	}
}

void Snake::checkItemColiisions(std::vector<std::shared_ptr<Item>>& items)
{
	for(auto it=items.begin(); it!=items.end() ; ++it){
		if(nodes_[0]->getBounds().intersects((*it)->getBounds())){
			if(std::dynamic_pointer_cast<Shield>(*it)){
				setShielded(true);
			}
			else if(std::dynamic_pointer_cast<Bonus>(*it)){
				bonusScore_ += 15 ;
			}
			else if(std::dynamic_pointer_cast<Clock>(*it)){
				Game::GameScreen_->addTimeLimit(20);
			}
			items.erase(it);
			pickupSound_.play();
			break;
		}
	}
}


void Snake::checkEdgeCollisions()
{
    auto& headNode = nodes_[0];

    // 单独检测水平方向边缘碰撞
    if (headNode->getPosition().x < 0)
        headNode->setPosition(Game::Width, headNode->getPosition().y);
    else if (headNode->getPosition().x >= Game::Width)
        headNode->setPosition(0, headNode->getPosition().y);

    // 单独检测垂直方向边缘碰撞
    if (headNode->getPosition().y < 0)
        headNode->setPosition(headNode->getPosition().x, Game::Height);
    else if (headNode->getPosition().y >= Game::Height)
        headNode->setPosition(headNode->getPosition().x, 0);
}

void Snake::setDirectionVector(sf::Vector2f& newDir) {
    float dotProduct = directionVector_.x * newDir.x + directionVector_.y * newDir.y;
	float magnitude = std::sqrt(newDir.x * newDir.x + newDir.y * newDir.y);
	dotProduct /= magnitude;
    if (dotProduct < -0.85) {  
        return;
    }
	newDir /= magnitude;
    directionVector_ = newDir;
}



void Snake::move()
{
	float k = 0.8;
	float velocity = 2 * k * nodes_[0]->NodeRadius_;
	for (decltype(nodes_.size()) i = nodes_.size() - 1; i > 0; --i)
	{
		nodes_[i]->setPosition(nodes_.at(i - 1)->getPosition());
		nodes_[i]->rotate(nodes_[i-1]->getRotation()-nodes_[i]->getRotation());
	}
	nodes_[0]->move(directionVector_.x * velocity , directionVector_.y * velocity);

}

void Snake::render(sf::RenderWindow& window) const
{
	for(const auto& node: nodes_){
		node->render(window);
	}

}