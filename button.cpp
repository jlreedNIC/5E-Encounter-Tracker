/**
 * @file button.cpp
 * @author Jordan Reed
 * @brief Program to track encounters for D&D 5E
 * @date 2020-12-10
 * 
 */

#include "button.h"

/**
 * @brief Default constructor for a button object. Initializes an empty button. Calls a constructor to RectangleShape and Text
 *        Sets an empty string, character size color and style of string. Sets the default button size and text position
 *        to the middle.
 * 
 */
Button::Button() : text(), rectangle()
{
    buttonString = "";
    text.setString(buttonString);
    text.setCharacterSize(25);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);

    setButtonSize();
    setTextPositionMiddle();
}

/**
 * @brief Constructs a new button object using a string for the text, and a font for the text. 
 *        Calls a constructor to RectangleShape and Text
 * 
 * @param buttonString String to initialize button text with
 * @param font Font to initialize the text with
 */
 // FIX: do I need to change to not a reference??
Button::Button(const std::string &buttonString, const sf::Font &font) : text(), rectangle()
{
    this->buttonString = buttonString;
    text.setString(this->buttonString);
    text.setFont(font);
    text.setCharacterSize(25);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);

    setButtonSize();
    setTextPositionMiddle();
}

/**
 * @brief Constructs a new button object using a string, font, and texture
 * 
 * @param buttonString String to use in the button text
 * @param font Font to apply to button text
 * @param texture Texture to apply to rectangle object
 */
Button::Button(const std::string &buttonString, const sf::Font &font, const sf::Texture &texture) : text(), rectangle()
{
    this->buttonString = buttonString;
    text.setString(this->buttonString);
    text.setCharacterSize(25);
    text.setFillColor(sf::Color::White);
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
    this->buttonString = buttonString;
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
    this->buttonString = buttonString;
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
    this->buttonString = buttonString;
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

/**
 * @brief Sets the texture for the rectangle object to use
 * 
 * @param texture Texture to apply to the button rectangle
 */
void Button::setTexture(const sf::Texture &texture)
{
    rectangle.setTexture(&texture);
}

/**
 * @brief Sets the size of the button relative to the string, so the button is bigger than the Text.
 * 
 */
 // FIX: potential issue here. size not working 
void Button::setButtonSize()
{
    sf::FloatRect textBound = text.getGlobalBounds();
    sf::Vector2f textSize = {textBound.width, textBound.height};
    textSize.x = std::max(textBound.width + 20, 0.f);
    textSize.y = std::max(textBound.height + 20, 0.f);
    rectangle.setSize(textSize);
}

/**
 * @brief Clears the texture from the rectangle object
 * 
 */
void Button::clearTexture()
{
    rectangle.setTexture(nullptr);
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
 // FIX: position not in middle of button. rough approximation
void Button::setTextPositionMiddle()
{
    sf::Vector2f rectanglePos = rectangle.getPosition();
    rectanglePos.x += 5;
    rectanglePos.y += 5;
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
 // FIX: underlying issue of buttonString being empty
std::string Button::getString()
{
    buttonString = text.getString();
    return buttonString;
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
 * @brief Returns the position of the rectangle object
 * 
 * @return sf::Vector2f Position of the rectangle in vector format
 */
sf::Vector2f Button::getPosition() const
{
    return rectangle.getPosition();
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

/**
 * @brief Draws both the text object and rectangle object to the target
 * 
 * @param target Target that the object is being drawn too
 * @param state 
 */
void Button::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
    target.draw(rectangle, state);
    target.draw(text, state);
}