#include "initiativelist.h"
#include <iostream>
#include <string>
#include "diceroll.h"
#include "button.h"
#include "app.h"
#include <SFML/Graphics.hpp>

int main()
{
    // // Button::font.loadFromFile("Fonts/Roboto-Thin.ttf");
    // // Button::texture.loadFromFile("Textures/button.png");
    // // //set textRect for tText?
    // // TextBox::tTexture.loadFromFile("Textures/fillable.png");

    // sf::RenderWindow window(sf::VideoMode(800,800), "D&D 5E Encounter Tracker");
    // window.setPosition(sf::Vector2i(10, 30));

    // //load fonts
    // sf::Font fontHeader;
    // if(!fontHeader.loadFromFile("Fonts/Sketch-Gothic-School.ttf"))
    // {
    //     //error
    // }
    // sf::Font fontButton;
    // if(!fontButton.loadFromFile("Fonts/Roboto-Thin.ttf"))
    // {
    //     //error
    // }
    // //create header
    // sf::Text textHeader("Encounter Tracker", fontHeader, 80);
    // textHeader.setFillColor(sf::Color::Black);
    // textHeader.setPosition(140,50);

    // // creating buttons on main menu

    // //new encounter button
    // Button newEButton("New Encounter", fontButton);
    // newEButton.setButtonPosition(300, 365);

    // // load encounter button
    // Button existingEButton;
    // existingEButton.setString("Load Encounter");
    // existingEButton.setFont(fontButton);
    // existingEButton.setButtonPosition(300, 465);

    // //initiative button
    // Button initiativeButton("Initiative Order", fontButton);
    // initiativeButton.setButtonPosition(300, 265);

    // // TextBox testing("testing");
    // // testing.setTextBoxPosition(50, 300);
    // // event loop
    // while(window.isOpen())
    // {
    //     sf::Event event;
    //     while(window.pollEvent(event))
    //     {
    //         if(event.type == sf::Event::Closed)
    //         {
    //             window.close();
    //         }
    //         if(event.type == sf::Event::MouseButtonPressed)
    //         {
    //             if(initiativeButton.isClicked(event.mouseButton.x, event.mouseButton.y))
    //             {
    //                 //run initiative loop
    //                 // initiativeGameLoop(window);
    //             }
    //             if(newEButton.isClicked(event.mouseButton.x, event.mouseButton.y))
    //             {
    //                 std::cout << "New Encounter\n";
    //             }
    //             if(existingEButton.isClicked(event.mouseButton.x, event.mouseButton.y))
    //             {
    //                 std::cout << "Load Encounter\n";
    //             }
    //         }
    //     }

    //     //draw
    //     window.clear(sf::Color::White);
    //     window.draw(textHeader);
    //     window.draw(newEButton);
    //     // window.draw(testing);
    //     // window.draw(testing.getText());
    //     window.draw(newEButton.getText());
    //     window.draw(existingEButton);
    //     window.draw(existingEButton.getText());
    //     window.draw(initiativeButton);
    //     window.draw(initiativeButton.getText());
    //     window.display();
    // }

    App app;
    app.mainMenu();
    return 0;
}