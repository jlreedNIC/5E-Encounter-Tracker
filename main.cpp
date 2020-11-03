#include "initiativelist.h"
#include <iostream>
#include "diceroll.h"
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800,800), "D&D 5E Encounter Tracker");


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
    }
    return 0;
}