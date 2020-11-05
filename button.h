#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>
#include <algorithm>

class Button : public sf::RectangleShape
{
    public:
        Button();
        Button(const std::string &buttonString);
        virtual ~Button();

        std::string& getString();
        sf::Text& getText();

        void setButtonString(const std::string &buttonString);
        void setButtonSize();
        void setButtonSize(const sf::Vector2f &size);
        void setTextPosition();

        void setButtonPosition(float x, float y);
        void setButtonPosition(const sf::Vector2f &position);

        bool isClicked(const float &x, const float &y);
        bool isClicked(const int &x, const int &y);
        bool isClicked(const sf::Vector2f &point);

        
        
    private:
        sf::Font buttonFont;
        sf::Text buttonText;
        sf::Texture buttonTexture;

        std::string buttonString;
};

#endif