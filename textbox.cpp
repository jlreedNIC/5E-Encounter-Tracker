/**
 * @file button.cpp
 * @author Jordan Reed
 * @brief Program to track encounters for D&D 5E
 * @date 2020-12-10
 * 
 */

#include "textbox.h"

/**
 * @brief Construct a new TextBox object. Sets the default character size, style, and color.
 *        Sets the size of the textBox and position of the Text object. Calls the Button constructor.
 * 
 */
TextBox::TextBox() : Button()
{
    text.setCharacterSize(20);
    text.setStyle(0);
    text.setFillColor(sf::Color::Black);

    setTextBoxSize(sf::Vector2f(0.f,0.f));
    setTextPositionLeft();
}

/**
 * @brief Construct a new TextBox object using a string and a font. Sets the default character 
 *        size, style, and color. Sets the size of the textBox and position of the Text object.
 *        Calls the button constructor.
 * 
 * @param tString String to use for the Text object
 * @param font Font to use for the Text object
 */
TextBox::TextBox(const std::string &tString, const sf::Font &font) : Button(tString, font)
{
    text.setCharacterSize(20);
    text.setStyle(0);
    text.setFillColor(sf::Color::Black);

    setTextBoxSize(sf::Vector2f(0.f,0.f));
    setTextPositionLeft();
}

/**
 * @brief Destroy the TextBox object
 * 
 */
TextBox::~TextBox()
{

}

// FIX: text.getGlobalBounds not getting bounds
// suspect issue in button class
/**
 * @brief Sets the size of the TextBox relative to the Text, so the textbox is not smaller
 *        than the size of the text. Will also compare to the passed parameter and set the
 *        size to the larger of the parameter or the text.
 * 
 * @param size Size that is desired for the text box
 */
void TextBox::setTextBoxSize(const sf::Vector2f &size)
{
    //either max of text size or parameter size
    sf::FloatRect textBound = text.getGlobalBounds();
    sf::Vector2f textSize = {textBound.width + 5, textBound.height + 5};
    textSize.x = std::max(textSize.x, size.x);
    textSize.y = std::max(textSize.y, size.y);
    rectangle.setSize(textSize);
}

/**
 * @brief Sets the string for the textBox
 * 
 * @param tstring String to use for the text object
 */
 // FIX: want to update size of text box with new string
void TextBox::setString(const std::string &tstring)
{
    text.setString(tstring);
    // setTextBoxSize(sf::Vector2f(0.f,0.f));
}

/**
 * @brief Sets the position of the rectangle object, then the text.
 * 
 * @param size Position of the rectangle
 */
void TextBox::setTextBoxPosition(const sf::Vector2f &size)
{
    rectangle.setPosition(size);
    setTextPositionLeft();
}

/**
 * @brief Sets the position of the rectangle object, then the text.
 * 
 * @param x X coordinate of the position desired
 * @param y Y coordinate of the position desired
 */
void TextBox::setTextBoxPosition(const float &x, const float &y)
{
    rectangle.setPosition(x, y);
    setTextPositionLeft();
}

/**
 * @brief  Sets the position of the rectangle object, then the text.
 * 
 * @param x X coordinate of the position desired
 * @param y Y coordinate of the position desired
 */
void TextBox::setTextBoxPosition(const int &x, const int &y)
{
    rectangle.setPosition(x, y);
    setTextPositionLeft();
}

/**
 * @brief Sets a generic outline for the rectangle object. Used in debugging.
 * 
 */
void TextBox::setOutline()
{
    rectangle.setOutlineColor(sf::Color::Black);
    rectangle.setOutlineThickness(2);
    rectangle.setFillColor(sf::Color::White);
}

/**
 * @brief Clears the outline on the rectangle.
 * 
 */
void TextBox::clearOutline()
{
    rectangle.setOutlineThickness(0);
}

/**
 * @brief Sets the position of the text object inside the rectangle and to the left
 * 
 */
void TextBox::setTextPositionLeft()
{
    sf::Vector2f rectanglePos = rectangle.getPosition();
    rectanglePos.x += 5;
    rectanglePos.y += 5;
    text.setPosition(rectanglePos);
}
