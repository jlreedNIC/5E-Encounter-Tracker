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

// sf::Font gRobotoFont; 
// gRobotoFont.loadFromFile("Fonts/Roboto-Thin.ttf");


class Button : public sf::RectangleShape
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
                                                                                // sets what's needed for the Text object
        void setString(const std::string &buttonString);        // sets the string for the button
        void setFont(const sf::Font &font);                     // sets the font for the button's Text object
        void setButtonSize(const sf::Vector2f &size);           // sets the minimum size of the button

        //want to overwrite setPosition
        void setButtonPosition(float x, float y);               // sets the position of both button and text
        void setButtonPosition(const sf::Vector2f &position);   // sets the position of both button and text
        
        // getters
        const std::string getString();      // gets the string that is on the button
        sf::Text& getText();                // returns a reference to text object for button

        // functions to see if button was clicked
        bool isClicked(const float &x, const float &y);
        bool isClicked(const int &x, const int &y);
        bool isClicked(const sf::Vector2f &point);

        // would like to implement
        // might need to change inheritance to drawable or shape
        // void draw(sf::RenderTarget& target, sf::RenderStates state) const
        // {
        //     // need to figure out how to draw both rectangle and text
        //     target.draw(m_vertices, state);
        //     target.draw(text);
        // }
        
    protected:
        void setTextPositionMiddle();       // sets the position of the text relative to the button
        void setButtonSize();               // sets the size of the button relative to the string

        sf::Text text;
};

#endif