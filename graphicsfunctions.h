#ifndef GRAPHICSFUNCTIONS_H
#define GRAPHICSFUNCTIONS_H

#include <SFML/Graphics.hpp>
#include <string>

void createButton(sf::RectangleShape &buttonShape, sf::Text &buttonText, sf::Font &buttonFont, std::string &buttonString);
void initiativeGameLoop(sf::RenderWindow &window);

#endif