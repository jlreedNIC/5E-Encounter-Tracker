/**
 * @file button.cpp
 * @author Jordan Reed
 * @brief Program to track encounters for D&D 5E
 * @date 2020-11-04
 * 
 */
#include "button.h"

/**
 * @brief Default constructor for a button object. Initializes an empty button. Calls a constructor to RectangleShape
 *        Sets an empty string, character size color and style of string. Sets the default button size and text position
 *        to the middle.
 * 
 */
Button::Button() : text(), rectangle()
{
    text.setString("");
    text.setCharacterSize(25);
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);

    setButtonSize();
    setTextPositionMiddle();
}

/**
 * @brief Constructs a new button object using a string for the text. Calls a constructor to RectangleShape
 * 
 * @param buttonString String to initialize button text with
 */
Button::Button(const std::string &buttonString, const sf::Font &font) : text(), rectangle()
{
    text.setString(buttonString);
    text.setFont(font);
    text.setCharacterSize(25);
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);

    setButtonSize();
    setTextPositionMiddle();
}

/**
 * @brief Constructs a new button object using a string, font, and texture
 * 
 * @param buttonString String to use in the button text
 * @param font Font to apply to button text
 * @param texture Texture to apply to button
 */
Button::Button(const std::string &buttonString, const sf::Font &font, const sf::Texture &texture) : text(), rectangle()
{
    text.setString(buttonString);
    text.setCharacterSize(25);
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);
    text.setFont(font);

    rectangle.setTexture(&texture);

    setButtonSize();
    setTextPositionMiddle();
}

/**
 * @brief Destroy the Button object
 * 
 */
Button::~Button()
{

}

/**
 * @brief Sets the Text string, Text font, and Texture for the button for after using the default constructor
 * 
 * @param buttonString String to use in the button text
 * @param font Font to apply to button text
 * @param texture Texture to apply to button 
 */
void Button::createButton(const std::string &buttonString, const sf::Font &font, const sf::Texture &texture)
{
    text.setString(buttonString);
    text.setCharacterSize(25);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setFont(font);

    rectangle.setTexture(&texture);

    setButtonSize();
    setTextPositionMiddle();
}

/**
 * @brief Sets just the parameters needed for the Text object
 * 
 * @param buttonString String to use in the button text
 * @param font Font to apply to button text
 */
void Button::setText(const std::string &buttonString, const sf::Font &font)
{
    text.setString(buttonString);
    text.setFont(font);
    text.setCharacterSize(25);
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);

    setButtonSize();
    setTextPositionMiddle();
}

/**
 * @brief Sets the string for the button to use, then sets the size and position of the string relative to the button
 * 
 * @param buttonString String to use for initialization
 */
void Button::setString(const std::string &buttonString)
{
    text.setString(buttonString);
    setButtonSize();
    setTextPositionMiddle();
}

/**
 * @brief Sets the font for the Text object to use
 * 
 * @param font Font to apply to button text
 */
void Button::setFont(const sf::Font &font)
{
    text.setFont(font);
}

void Button::setTexture(const sf::Texture &texture)
{
    rectangle.setTexture(&texture);
}

/**
 * @brief Sets the size of the button relative to the string, so the button is bigger than the Text.
 * 
 */
void Button::setButtonSize()
{
    sf::FloatRect textBound = text.getGlobalBounds();
    sf::Vector2f textSize = {textBound.width + 10, textBound.height};
    textSize.x = std::max(textBound.width + 20, 0.f);
    textSize.y = std::max(textBound.height + 30, 0.f);
    rectangle.setSize(textSize);
}

/**
 * @brief Sets the position of both button and text given 2 float values
 * 
 * @param x X coordinate of the button
 * @param y Y coordinate of the button
 */
void Button::setButtonPosition(float x, float y)
{
    rectangle.setPosition(x, y);
    setTextPositionMiddle();
}

/**
 * @brief Sets the position of both button and text given a vector of floats
 * 
 * @param position X and Y coordinates in a vector
 */
void Button::setButtonPosition(const sf::Vector2f &position)
{
    rectangle.setPosition(position);
    setTextPositionMiddle();
}

/**
 * @brief Sets the position of the text relative to the button. Will be in the middle of the button
 * 
 */
void Button::setTextPositionMiddle()
{
    sf::Vector2f rectanglePos = rectangle.getPosition();
    rectanglePos.x += 10;
    rectanglePos.y += 10;
    text.setPosition(rectanglePos);
}

/**
 * @brief Resets the button size if it is smaller than the parameter.
 * 
 * @param size The minimum size wanted for the button.
 */
void Button::setButtonSize(const sf::Vector2f &size)
{
    setButtonSize();

    sf::Vector2f currentSize = rectangle.getSize();
    if(currentSize.x < size.x && currentSize.y < size.y)
    {
        rectangle.setSize(size);
    }
    else if(currentSize.x < size.x)
    {
        currentSize.x = size.x;
        rectangle.setSize(currentSize);
    }
    else if(currentSize.y < size.y)
    {
        currentSize.y = size.y;
        rectangle.setSize(currentSize);
    }
    setTextPositionMiddle();
}

/**
 * @brief Returns the string used in the button
 * 
 * @return std::string A copy of the string for the button
 */
const std::string Button::getString()
{
    return text.getString();
}

/**
 * @brief Returns the Text object used in the button
 * 
 * @return sf::Text& A reference to the Text object for the button
 */
sf::Text& Button::getText()
{
    return text;
}

/**
 * @brief Checks to see if the button was clicked given float coordinates
 * 
 * @param x X coordinate of mouse click
 * @param y Y coordinate of mouse click
 * @return true When button has been clicked, or coordinates are within the shape of the button
 * @return false When button has not been clicked, or coordinates are outside the shape of the button
 */
bool Button::isClicked(const float &x, const float &y)
{
    sf::FloatRect buttonBound = rectangle.getGlobalBounds();
    return buttonBound.contains(sf::Vector2f(x,y));
}

/**
 * @brief Checks to see if the button was clicked given integer coordinates
 * 
 * @param x X coordinate of mouse click
 * @param y Y coordinate of mouse click
 * @return true When button has been clicked, or coordinates are within the shape of the button
 * @return false When button has not been clicked, or coordinates are outside the shape of the button
 */
bool Button::isClicked(const int &x, const int &y)
{
    float posX = x;
    float posY = y;
    sf::FloatRect buttonBound = rectangle.getGlobalBounds();
    return buttonBound.contains(sf::Vector2f(posX,posY));
}

/**
 * @brief Checks to see if the button was clicked given coordinates in vector form
 * 
 * @param x X coordinate of mouse click
 * @param y Y coordinate of mouse click
 * @return true When button has been clicked, or coordinates are within the shape of the button
 * @return false When button has not been clicked, or coordinates are outside the shape of the button
 */
bool Button::isClicked(const sf::Vector2f &point)
{
    sf::FloatRect buttonBound = rectangle.getGlobalBounds();
    return buttonBound.contains(point);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
    target.draw(rectangle, state);
    target.draw(text, state);
}