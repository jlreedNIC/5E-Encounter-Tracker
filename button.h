/**
 * @file button.h
 * @author Jordan Reed
 * @brief Program to track encounters for D&D 5E
 * @date 2020-11-04
 * 
 */
#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>
#include <algorithm>

class Button : public sf::RectangleShape
{
    public:
        Button();                                   // default constructor
        Button(const std::string &buttonString);    // convert string to button constructor
        virtual ~Button();                          // destructor

        const std::string getString();      // returns a reference to string for button
        sf::Text& getText();                // returns a reference to text object for button

        void setString(const std::string &buttonString);        // sets the string for the button
        void setFont(const std::string &fileName);              // passes the filename for a font to set the font to
        void setButtonSize(const sf::Vector2f &size);           // sets the minimum size of the button

        // void draw(sf::RenderTarget& target, sf::RenderStates state) const
        // {
        //     // need to figure out how to draw both rectangle and text
        //     target.draw(text);
        // }

        //want to overwrite setPosition
        void setButtonPosition(float x, float y);               // sets the position of both button and text
        void setButtonPosition(const sf::Vector2f &position);   // sets the position of both button and text

        bool isClicked(const float &x, const float &y);         // checks to see if button was clicked
        bool isClicked(const int &x, const int &y);             // checks to see if button was clicked
        bool isClicked(const sf::Vector2f &point);              // checks to see if button was clicked

        
        
    protected:
        void setTextPositionMiddle();                           // sets the position of the text relative to the button
        void setButtonSize();                                   // sets the size of the button relative to the string

        sf::Font font;
        sf::Text text;

        sf::Texture texture;
};

#endif