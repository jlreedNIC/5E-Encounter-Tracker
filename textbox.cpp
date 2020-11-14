#include "textbox.h"

TextBox::TextBox() : Button()
{
    text.setCharacterSize(20);
    text.setStyle(0);

}

TextBox::TextBox(const std::string &tString) : Button(tString)
{
    text.setCharacterSize(20);
    text.setStyle(0);
    setTextBoxSize(sf::Vector2f(0.f,0.f));
}

TextBox::~TextBox()
{

}

void TextBox::setTextBoxSize(const sf::Vector2f &size)
{
    //either max of text size or parameter size
    sf::FloatRect textBound = text.getGlobalBounds();
    sf::Vector2f textSize = {textBound.width + 10, textBound.height + 10};
    textSize.x = std::max(textSize.x, size.x);
    textSize.y = std::max(textSize.y, size.y);
    setSize(textSize);
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
