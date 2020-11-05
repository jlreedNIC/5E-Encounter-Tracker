#include "initiativelist.h"
#include <iostream>
#include "diceroll.h"
#include "graphicsfunctions.h"
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800,800), "D&D 5E Encounter Tracker");
    window.setPosition(sf::Vector2i(10, 30));

    //load fonts
    sf::Font fontHeader;
    if(!fontHeader.loadFromFile("Fonts/Sketch-Gothic-School.ttf"))
    {
        //error
    }
    sf::Font fontButton;
    if(!fontButton.loadFromFile("Fonts/Roboto-Thin.ttf"))
    {
        //error
    }
    //create header
    sf::Text textHeader("Encounter Tracker", fontHeader, 80);
    textHeader.setFillColor(sf::Color::Black);
    textHeader.setPosition(120,50);

    //creating buttons on main menu

    //new encounter button
    sf::Text newButtonText;
    sf::RectangleShape newButton;
    string buttonText = "New Encounter";
    createButton(newButton, newButtonText, fontButton, buttonText);
    newButtonText.setPosition(480, 315);
    newButton.setPosition(475, 300);

    //existing encounter button
    buttonText = "Existing Encounter";
    sf::Text existingButtonText;
    sf::RectangleShape existingButton;
    createButton(existingButton, existingButtonText, fontButton, buttonText);
    existingButtonText.setPosition(480, 415);
    existingButton.setPosition(475, 400);

    //initiative button
    buttonText = "Initiative Order";
    sf::Text initiativeButtonText;
    sf::RectangleShape initiativeButton;
    createButton(initiativeButton, initiativeButtonText, fontButton, buttonText);
    initiativeButtonText.setPosition(180, 315);
    initiativeButton.setPosition(160, 300);
    sf::FloatRect initBound = initiativeButton.getGlobalBounds();

    sf::Texture buttonTexture;
    buttonTexture.loadFromFile("Textures/button.png");
    initiativeButton.setTexture(&buttonTexture);
    existingButton.setTexture(&buttonTexture);
    newButton.setTexture(&buttonTexture);

    bool clickedButton = false;

    //event loop
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
                if(initBound.contains(mouseClick))
                {
                    //run initiative loop
                    initiativeGameLoop(window);
                }
            }
        }

        //draw
        window.clear(sf::Color::White);
        window.draw(textHeader);
        window.draw(newButton);
        window.draw(newButtonText);
        window.draw(existingButton);
        window.draw(existingButtonText);
        window.draw(initiativeButton);
        window.draw(initiativeButtonText);
        window.display();
    }
    return 0;
}