#include "textbox.h"

TextBox::TextBox() : Button()
{
    text.setCharacterSize(20);
    text.setStyle(0);
    setTextBoxSize(sf::Vector2f(0.f, 0.f));
    setTextPositionLeft();
    texture.loadFromFile(nullptr);
    setTexture(nullptr);
    setFillColor(sf::Color::White);
    setOutlineColor(sf::Color::Black);
    setOutlineThickness(2);
}

TextBox::TextBox(const std::string &tString) : Button(tString)
{
    text.setCharacterSize(20);
    text.setStyle(0);
    setTextBoxSize(sf::Vector2f(0.f,0.f));
    setTextPositionLeft();
    setTexture(nullptr);
    setFillColor(sf::Color::White);
    setOutlineColor(sf::Color::Black);
    setOutlineThickness(2);
}

TextBox::~TextBox()
{

}

void TextBox::setTextBoxSize(const sf::Vector2f &size)
{
    //either max of text size or parameter size
    sf::FloatRect textBound = text.getGlobalBounds();
    sf::Vector2f textSize = {textBound.width + 20, textBound.height + 20};
    textSize.x = std::max(textSize.x, size.x);
    textSize.y = std::max(textSize.y, size.y);
    setSize(textSize);
}

void TextBox::setTextBoxPosition(const sf::Vector2f &size)
{
    setPosition(size);
    setTextPositionLeft();
}

void TextBox::setTextBoxPosition(const float &x, const float &y)
{
    setPosition(x, y);
    setTextPositionLeft();
}

void TextBox::setTextPositionLeft()
{
    sf::Vector2f rectanglePos = getPosition();
    rectanglePos.x += 5;
    rectanglePos.y += 5;
    text.setPosition(rectanglePos);
}
