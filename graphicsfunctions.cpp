#include "graphicsfunctions.h"

void createButton(sf::RectangleShape &buttonShape, sf::Text &buttonText, sf::Font &buttonFont, std::string &buttonString)
{
    //set text
    buttonText.setFont(buttonFont);
    buttonText.setString(buttonString);
    buttonText.setFillColor(sf::Color::Black);
    buttonText.setCharacterSize(25);
    buttonText.setStyle(sf::Text::Bold);

    //set shape
    buttonShape.setSize(sf::Vector2f(210.f, 60.f));
    // buttonShape.setFillColor(sf::Color::Black);
    // buttonShape.setOutlineThickness(2.f);
    // buttonShape.setOutlineColor(sf::Color::Red);

    // sf::Texture buttonTexture;
    // buttonTexture.loadFromFile("Sprites/button.png");
    // // sf::Sprite buttonSprite;
    // // buttonSprite.loadFromFile("Sprites/button.png");
    // buttonShape.setTexture(&buttonTexture);
}

void initiativeGameLoop(sf::RenderWindow &window)
{
    sf::RectangleShape exitButton;
    sf::Text exitText;
    sf::Font buttonFont;
    buttonFont.loadFromFile("Fonts/Roboto-Thin.ttf");
    std::string exitString = "Exit";
    createButton(exitButton, exitText, buttonFont, exitString);
    exitButton.setPosition(50, 700);
    exitText.setPosition(100, 715);
    sf::FloatRect exitBound = exitButton.getGlobalBounds();
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }

            if(event.type == sf::Event::MouseButtonPressed)
            {
                float posX = event.mouseButton.x;
                float posY = event.mouseButton.y;
                sf::Vector2f mouseClick = {posX, posY};
                if(exitBound.contains(mouseClick))
                {
                    return;
                }
            }

            window.clear(sf::Color::White);
            window.draw(exitButton);
            window.draw(exitText);
            window.display();
        }
    }
}