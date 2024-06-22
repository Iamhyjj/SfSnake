#ifndef OBS
#define OBS

#include <SFML/Graphics.hpp>
class Obstacle
{
    public:
        Obstacle(sf::Vector2f&);
        void render(sf::RenderWindow&) const;
        static const float Radius;
        sf::Vector2f getPostion() const;
        sf::FloatRect getBounds() const;
        void rotate();
    private:
        sf::Sprite obsSrite_;
        static const sf::Texture obsTexture_;
        float angularVelocity_;
};




#endif