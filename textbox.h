#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "button.h"
#include <iostream>

class TextBox : public Button
{
    public:
        TextBox();
        TextBox(const std::string &tString, const sf::Font &font);
        ~TextBox();

        void setTextBoxSize(const sf::Vector2f &size);
        void setString(const std::string &tstring);

        void setTextBoxPosition(const sf::Vector2f &size);
        void setTextBoxPosition(const float &x, const float &y);
        void setTextBoxPosition(const int &x, const int &y);

        void setOutline();
        void clearOutline();

        static sf::Texture tTexture;
    private:
        void setTextPositionLeft();
};

#endif