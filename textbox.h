#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "button.h"
// #include <string>

class TextBox : public Button
{
    public:
        TextBox();
        TextBox(const std::string &tString);
        ~TextBox();

        void setTextBoxSize(const sf::Vector2f &size);

        void setTextBoxPosition(const sf::Vector2f &size);
        void setTextBoxPosition(const float &x, const float &y);
        void setTextBoxPosition(const int &x, const int &y);


    private:
        void setTextPositionLeft();
};

#endif