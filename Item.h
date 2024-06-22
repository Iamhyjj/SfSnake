#ifndef ITEM_H
#define ITEM_H

#include <memory>

#include <SFML/Graphics.hpp>

class Item
{
    public:
        Item(sf::Vector2f&);
        void render(sf::RenderWindow&) const;
        sf::FloatRect getBounds() const;
        virtual ~Item(){};
        static const int itemTypeNum;
    protected:
        sf::Sprite itemSprite_;
        
};

class Shield : public Item
{
    public:
        Shield(sf::Vector2f&);
    private:
        static const sf::Texture shieldTexture_;
};

class Bonus : public Item
{
    public:
        Bonus(sf::Vector2f&);
    private:
        static const sf::Texture bonusTexture_;
};

class Clock : public Item
{
    public:
        Clock(sf::Vector2f&);
    private:
        static const sf::Texture clockTexture_;
};

#endif