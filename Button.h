#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>

namespace sfSnake
{
    class Button{
        public:
            Button();
            void setPosition(const sf::Vector2f&);
            void render(sf::RenderWindow& window) const;
            bool isHovered(sf::RenderWindow& window) const;
            virtual void activate(sf::RenderWindow& window){};
            void setText(const sf::String&);
            sf::FloatRect getBounds() const;

            static const float width;
            static const float height;
        protected:
            sf::RectangleShape shape_;
            sf::Text text_;
            sf::Font font_;
    };

    class ShowGridButton : public Button
    {
        public:
            void activate(sf::RenderWindow& window) override;
            ShowGridButton();
        private:
            bool showGrid_;
    };
    
    class BackgroundColorButton : public Button
    {
        public:
            void activate(sf::RenderWindow&) override;
            BackgroundColorButton();
            sf::Color getBackgroundColor() const;
        private:
            sf::Color backgroundColor_ ;
    };

    class MusicButton : public Button
    {

    };

} // namespace sfSnake

#endif