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
#include <iostream>

class Button : public sf::Drawable
{
    public:
        // constructors and destructor
        Button();
        Button(const std::string &buttonString, const sf::Font &font);
        Button(const std::string &buttonString, const sf::Font &font, const sf::Texture &texture);
        virtual ~Button();

        // setters
        void createButton(const std::string &buttonString, const sf::Font &font, const sf::Texture &texture);   // sets everything needed for button
        void setText(const std::string &buttonString, const sf::Font &font);    // sets the string and font
                                                                                // sets what's needed for the Text object only
        void setString(const std::string &buttonString);        // sets the string for the button
        void setFont(const sf::Font &font);                     // sets the font for the button's Text object
        void setTexture(const sf::Texture &texture);            // sets the texture for the rectangle object
        void setButtonSize(const sf::Vector2f &size);           // sets the minimum size of the button

        void clearTexture();                                    // clears the texture on the button

        //want to overwrite to setPosition
        void setButtonPosition(float x, float y);               // sets the position of both button and text
        void setButtonPosition(const sf::Vector2f &position);   // sets the position of both button and text
        
        // getters
        std::string getString();            // gets the string that is on the button
        sf::Text& getText();                // returns a reference to text object for button
        sf::Vector2f getPosition() const;   // returns the position of the rectangle object of the button

        // functions to see if button was clicked
        bool isClicked(const float &x, const float &y);
        bool isClicked(const int &x, const int &y);
        bool isClicked(const sf::Vector2f &point);

        // draws the button to the target
        void draw(sf::RenderTarget& target, sf::RenderStates state) const;
        
    protected:
        void setTextPositionMiddle();       // sets the position of the text relative to the button
        void setButtonSize();               // sets the size of the button relative to the string

        std::string buttonString;           // the string that is on the button
        sf::Text text;
        sf::RectangleShape rectangle;
};

#endif