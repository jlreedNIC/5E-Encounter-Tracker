#include "graphicsfunctions.h"

void createButton(sf::RectangleShape &buttonShape, sf::Text &buttonText, sf::Font &buttonFont, std::string &buttonString)
{
    //set text
    buttonText.setFont(buttonFont);
    buttonText.setString(buttonString);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setCharacterSize(25);
    buttonText.setStyle(sf::Text::Bold);

    //set shape
    buttonShape.setSize(sf::Vector2f(210.f, 60.f));
    buttonShape.setFillColor(sf::Color::Black);
    buttonShape.setOutlineThickness(2.f);
    buttonShape.setOutlineColor(sf::Color::Red);
}