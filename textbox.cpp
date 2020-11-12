#include "textbox.h"

TextBox::TextBox() : Button()
{
    if(!font.loadFromFile("Fonts/Roboto-Thin.ttf"))
    {
        //error loading file
    }
    text.setFont(font);
    text.setString("");
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);

}

TextBox::TextBox(const std::string &tString) : Button()
{
    if(!font.loadFromFile("Fonts/Roboto-Thin.ttf"))
    {
        //error loading file
    }
    text.setFont(font);
    text.setString(tString);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);
}

TextBox::~TextBox()
{

}

void TextBox::setTextBoxSize(const sf::Vector2f &size)
{

}

void TextBox::setTextBoxPosition(const sf::Vector2f &size)
{

}

void TextBox::setTextBoxPosition(const float &x, const float &y)
{

}

void TextBox::setTextPositionLeft()
{

}
