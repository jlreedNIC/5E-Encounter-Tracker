/**
 * @file button.cpp
 * @author Jordan Reed
 * @brief Program to track encounters for D&D 5E
 * @date 2020-12-10
 * 
 */

#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "button.h"
#include <iostream>

class TextBox : public Button
{
    public:
        // constructors and destructor
        TextBox();
        TextBox(const std::string &tString, const sf::Font &font);
        virtual ~TextBox();

        // setters
        void setTextBoxSize(const sf::Vector2f &size);              // sets the textbox size
        void setString(const std::string &tstring);                 // sets the textbox string

        void setTextBoxPosition(const sf::Vector2f &size);          // sets the position of textbox
        void setTextBoxPosition(const float &x, const float &y);    // sets the position of textbox
        void setTextBoxPosition(const int &x, const int &y);        // sets the position of textbox

        void setOutline();      // sets a generic outline for the textbox
                                // used in debugging
        void clearOutline();    // clears the outline of the textbox

    private:
        void setTextPositionLeft(); // sets the text to the left of the textbox
};

#endif