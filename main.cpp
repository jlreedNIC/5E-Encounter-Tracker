#include "initiativelist.h"
#include <iostream>
#include "diceroll.h"
#include "graphicsfunctions.h"
#include "button.h"
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
    textHeader.setPosition(140,50);

    //creating buttons on main menu

    //new encounter button
    Button newEButton("New Encounter");
    newEButton.setButtonPosition(300, 365);

    // load encounter button
    Button existingEButton;
    existingEButton.setButtonString("Load Encounter");
    existingEButton.setButtonPosition(300, 465);

    //initiative button
    Button initiativeButton("Initiative Order");
    initiativeButton.setButtonPosition(300, 265);

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
                if(initiativeButton.isClicked(event.mouseButton.x, event.mouseButton.y))
                {
                    //run initiative loop
                    initiativeGameLoop(window);
                }
                if(newEButton.isClicked(event.mouseButton.x, event.mouseButton.y))
                {
                    std::cout << "New Encounter\n";
                }
                if(existingEButton.isClicked(event.mouseButton.x, event.mouseButton.y))
                {
                    std::cout << "Load Encounter\n";
                }
            }
        }

        //draw
        window.clear(sf::Color::White);
        window.draw(textHeader);
        window.draw(newEButton);
        window.draw(newEButton.getText());
        window.draw(existingEButton);
        window.draw(existingEButton.getText());
        window.draw(initiativeButton);
        window.draw(initiativeButton.getText());
        window.display();
    }
    return 0;
}