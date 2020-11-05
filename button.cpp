#include "button.h"

Button::Button() : RectangleShape()	
{
    //font and text
    if(!buttonFont.loadFromFile("Fonts/Roboto-Thin.ttf"))
    {
        //error loading font
    }
    buttonString = "";
    buttonText.setString(buttonString);
    buttonText.setFont(buttonFont);
    buttonText.setCharacterSize(25);
    buttonText.setFillColor(sf::Color::Black);
    buttonText.setStyle(sf::Text::Bold);

    //button texture
    if(buttonTexture.loadFromFile("Textures/button.png"))
    {
        //error loading texture
    }
    setTexture(&buttonTexture);

    setButtonSize();
    setTextPosition();
}

Button::Button(const std::string &buttonString) : RectangleShape()
{
    //font and text
    if(!buttonFont.loadFromFile("Fonts/Roboto-Thin.ttf"))
    {
        //error loading font
    }
    this->buttonString = buttonString;
    buttonText.setString(buttonString);
    buttonText.setFont(buttonFont);
    buttonText.setCharacterSize(25);
    buttonText.setFillColor(sf::Color::Black);
    buttonText.setStyle(sf::Text::Bold);

    //button texture
    if(buttonTexture.loadFromFile("Textures/button.png"))
    {
        //error loading texture
    }
    setTexture(&buttonTexture);

    setButtonSize();
    setTextPosition();
}

Button::~Button()
{

}

std::string& Button::getString()
{
    return buttonString;
}

sf::Text& Button::getText()
{
    return buttonText;
}

void Button::setButtonString(const std::string &buttonString)
{
    this->buttonString = buttonString;
    buttonText.setString(buttonString);
    setButtonSize();
    setTextPosition();
}

void Button::setButtonSize()
{
    sf::FloatRect textBound = buttonText.getGlobalBounds();
    sf::Vector2f textSize = {textBound.width + 20, textBound.height + 30};
    // textSize.x = std::max(textBound.width + 20, 100.f);
    textSize.y = std::max(textBound.height + 30, 55.f);
    setSize(textSize);
}

void Button::setButtonSize(const sf::Vector2f &size)
{
    setButtonSize();

    sf::Vector2f currentSize = getSize();
    if(currentSize.x < size.x && currentSize.y < size.y)
    {
        setSize(size);
    }
    else if(currentSize.x < size.x)
    {
        currentSize.x = size.x;
        setSize(currentSize);
    }
    else if(currentSize.y < size.y)
    {
        currentSize.y = size.y;
        setSize(currentSize);
    }
    setTextPosition();
}

void Button::setTextPosition()
{
    sf::Vector2f rectanglePos = getPosition();
    rectanglePos.x += 10;
    rectanglePos.y += 10;
    buttonText.setPosition(rectanglePos);
}

void Button::setButtonPosition(float x, float y)
{
    setPosition(x, y);
    setTextPosition();
}

void Button::setButtonPosition(const sf::Vector2f &position)
{
    setPosition(position);
    setTextPosition();
}

bool Button::isClicked(const float &x, const float &y)
{
    sf::FloatRect buttonBound = getGlobalBounds();
    return buttonBound.contains(sf::Vector2f(x,y));
}

bool Button::isClicked(const int &x, const int &y)
{
    float posX = x;
    float posY = y;
    sf::FloatRect buttonBound = getGlobalBounds();
    return buttonBound.contains(sf::Vector2f(posX,posY));
}

bool Button::isClicked(const sf::Vector2f &point)
{
    sf::FloatRect buttonBound = getGlobalBounds();
    return buttonBound.contains(point);
}