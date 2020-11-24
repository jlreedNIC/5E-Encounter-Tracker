#include "textbox.h"

sf::Texture TextBox::tTexture;

TextBox::TextBox() : Button()
{
    text.setCharacterSize(20);
    text.setStyle(0);
    text.setFillColor(sf::Color::Black);

    setTextBoxSize(sf::Vector2f(0.f,0.f));
    setTextPositionLeft();

    // rectangle.setFillColor(sf::Color::Red);
    // rectangle.setOutlineColor(sf::Color::Red);
    // rectangle.setOutlineThickness(1);
}

TextBox::TextBox(const std::string &tString, const sf::Font &font) : Button(tString, font)
{
    text.setCharacterSize(20);
    text.setStyle(0);
    text.setFillColor(sf::Color::Black);

    setTextBoxSize(sf::Vector2f(0.f,0.f));
    setTextPositionLeft();

    // setFillColor(sf::Color::White);
    // setOutlineColor(sf::Color::Black);
    // setOutlineThickness(2);
    // setTexture(nullptr);
}

TextBox::~TextBox()
{

}

void TextBox::setTextBoxSize(const sf::Vector2f &size)
{
    //either max of text size or parameter size
    sf::FloatRect textBound = text.getGlobalBounds();
    sf::Vector2f textSize = {textBound.width + 10.f, textBound.height + 10.f};
    textSize.x = std::max(textSize.x, size.x);
    textSize.y = std::max(textSize.y, size.y);
    rectangle.setSize(textSize);
}

void TextBox::setString(const std::string &tstring)
{
    text.setString(tstring);
}

void TextBox::setTextBoxPosition(const sf::Vector2f &size)
{
    rectangle.setPosition(size);
    setTextPositionLeft();
}

void TextBox::setTextBoxPosition(const float &x, const float &y)
{
    rectangle.setPosition(x, y);
    setTextPositionLeft();
}

void TextBox::setTextBoxPosition(const int &x, const int &y)
{
    rectangle.setPosition(x, y);
    setTextPositionLeft();
}

void TextBox::setTextPositionLeft()
{
    sf::Vector2f rectanglePos = rectangle.getPosition();
    rectanglePos.x += 5;
    rectanglePos.y += 5;
    text.setPosition(rectanglePos);
}
