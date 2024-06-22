#ifndef SNAKE_NODE_H
#define SNAKE_NODE_H
#include <cmath>
#include <SFML/Graphics.hpp>

namespace sfSnake
{

class SnakeNode
{
public:
	SnakeNode(sf::Vector2f position = sf::Vector2f(0, 0));
	void setPosition(sf::Vector2f position);
	void setPosition(float x, float y);
	void move(float xOffset, float yOffset);
	void initTexture();
	void render(sf::RenderWindow& window);
	float getRotation() const;
	void rotate(float);
	virtual void setShieldedTexture(bool)=0;
	sf::Vector2f getPosition() const;
	sf::FloatRect getBounds() const;

	
	static const float NodeRadius_;


protected:
	static const sf::Texture headTexture_;
	static const sf::Texture bodyTexture_;
	static const sf::Texture shieldedHeadTexture_;
	sf::Vector2f position_;
	sf::Sprite sprite_;
	float angle_;

};

class SnakeHead : public SnakeNode
{
	public:
		SnakeHead(sf::Vector2f&);
		virtual	void setShieldedTexture(bool) override;
};

class SnakeBody : public SnakeNode
{
	public:
		SnakeBody(sf::Vector2f&);
		virtual void setShieldedTexture(bool)override{};
};


}//namespace sfSnake

#endif