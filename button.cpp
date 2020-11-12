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
 * 
 */
Button::Button() : RectangleShape()	
{
    //font and text
    if(!font.loadFromFile("Fonts/Roboto-Thin.ttf"))
    {
        //error loading font
    }
    text.setString("");
    text.setFont(font);
    text.setCharacterSize(25);
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);

    //button texture
    if(texture.loadFromFile("Textures/button.png"))
    {
        //error loading texture
    }
    setTexture(&texture);

    setButtonSize();
    setTextPositionMiddle();
}

/**
 * @brief Constructs a new button object using a string for the text. Calls a constructor to RectangleShape
 * 
 * @param buttonString String to initialize button text with
 */
Button::Button(const std::string &buttonString) : RectangleShape()
{
    //font and text
    if(!font.loadFromFile("Fonts/Roboto-Thin.ttf"))
    {
        //error loading font
    }
    text.setString(buttonString);
    text.setFont(font);
    text.setCharacterSize(25);
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);

    //button texture
    if(texture.loadFromFile("Textures/button.png"))
    {
        //error loading texture
    }
    setTexture(&texture);

    setButtonSize();
    setTextPositionMiddle();
}

/**
 * @brief Destroy the Button:: Button object
 * 
 */
Button::~Button()
{

}

/**
 * @brief Returns the string used in the button
 * 
 * @return std::string& A reference to the string for the button
 */
const std::string& Button::getString()
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

void Button::setFont(const std::string &fileName)
{
    if(!font.loadFromFile(fileName))
    {
        // error loading font
    }
}

/**
 * @brief Sets the size of the button relative to the string, so the button is bigger than the Text.
 * 
 */
void Button::setButtonSize()
{
    sf::FloatRect textBound = text.getGlobalBounds();
    sf::Vector2f textSize = {textBound.width + 20, textBound.height + 30};
    textSize.x = std::max(textBound.width + 20, 100.f);
    textSize.y = std::max(textBound.height + 30, 55.f);
    setSize(textSize);
}

/**
 * @brief Resets the button size if it is smaller than the parameter.
 * 
 * @param size The minimum size wanted for the button.
 */
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
    setTextPositionMiddle();
}

/**
 * @brief Sets the position of the text relative to the button. Will be in the middle of the button
 * 
 */
void Button::setTextPositionMiddle()
{
    sf::Vector2f rectanglePos = getPosition();
    rectanglePos.x += 10;
    rectanglePos.y += 10;
    text.setPosition(rectanglePos);
}

/**
 * @brief Sets the position of both button and text given 2 float values
 * 
 * @param x X coordinate of the button
 * @param y Y coordinate of the button
 */
void Button::setButtonPosition(float x, float y)
{
    setPosition(x, y);
    setTextPositionMiddle();
}

/**
 * @brief Sets the position of both button and text given a vector of floats
 * 
 * @param position X and Y coordinates in a vector
 */
void Button::setButtonPosition(const sf::Vector2f &position)
{
    setPosition(position);
    setTextPositionMiddle();
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
    sf::FloatRect buttonBound = getGlobalBounds();
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
    sf::FloatRect buttonBound = getGlobalBounds();
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
    sf::FloatRect buttonBound = getGlobalBounds();
    return buttonBound.contains(point);
}