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
    sf::Text textHeader;
    textHeader.setFont(fontHeader);
    textHeader.setString("Initiative Tracker");
    textHeader.setFillColor(sf::Color::Black);
    textHeader.setCharacterSize(80);
    textHeader.setPosition(120,50);

    //creating buttons on main menu
    sf::Text newButtonText;
    // newButtonText.setFont(fontButton);
    // newButtonText.setString("New Initiative");
    // newButtonText.setFillColor(sf::Color::White);
    // newButtonText.setCharacterSize(25);
    // newButtonText.setStyle(sf::Text::Bold);
    // newButtonText.setPosition(300, 315);

    sf::RectangleShape newButton(sf::Vector2f(210.f, 60.f));
    // newButton.setFillColor(sf::Color::Black);
    // newButton.setOutlineThickness(2.f);
    // newButton.setOutlineColor(sf::Color::Red);
    // newButton.setPosition(275, 300);

    string buttonText = "New Initiative";
    createButton(newButton, newButtonText, fontButton, buttonText);
    newButtonText.setPosition(300, 315);
    newButton.setPosition(275, 300);

    buttonText = "Existing Initiative";
    sf::Text existingButtonText;
    // existingButtonText.setFont(fontButton);
    // existingButtonText.setString("Existing Initiative");
    // existingButtonText.setFillColor(sf::Color::White);
    // existingButtonText.setCharacterSize(25);
    // existingButtonText.setStyle(sf::Text::Bold);
    // 

    sf::RectangleShape existingButton(sf::Vector2f(210.f, 60.f));
    // existingButton.setFillColor(sf::Color::Black);
    // existingButton.setPosition(275, 400);
    // existingButton.setOutlineThickness(2.f);
    // existingButton.setOutlineColor(sf::Color::Red);
    createButton(existingButton, existingButtonText, fontButton, buttonText);
    existingButtonText.setPosition(280, 415);
    existingButton.setPosition(275, 400);

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
        }

        //draw
        window.clear(sf::Color::White);
        window.draw(textHeader);
        window.draw(newButton);
        window.draw(newButtonText);
        window.draw(existingButton);
        window.draw(existingButtonText);
        window.display();
    }
    return 0;
}