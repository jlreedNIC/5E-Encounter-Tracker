#include "graphicsfunctions.h"


void initiativeGameLoop(sf::RenderWindow &window)
{
    Button exitButton("Exit");
    exitButton.setButtonPosition(50, 700);

    sf::Text header[6];
    sf::Font headerFont;
    if(!headerFont.loadFromFile("Fonts/Roboto-Thin.ttf"))
    {
        //error
    }
    header[0].setString("Initiative");
    header[1].setString("Name");
    header[2].setString("AC");
    header[3].setString("Health");
    header[4].setString("Temp Health");
    header[5].setString("Status");

    header[0].setPosition( 50, 25);
    header[1].setPosition(150, 25);
    header[2].setPosition(300, 25);
    header[3].setPosition(375, 25);
    header[4].setPosition(475, 25);
    header[5].setPosition(625, 25);

    for(int i=0; i<6; i++)
    {
        header[i].setFont(headerFont);
        header[i].setCharacterSize(20);
        header[i].setFillColor(sf::Color::Black);
        header[i].setStyle(sf::Text::Bold);
    }
    
    // Creature(string name, int maxHealth, int health, int tempHealth, int initiative, int armorClass, string status)
    Initiative initList;
    initList.addNodeInOrder(Creature("Rihala", 33, 33, 0, 1, 11, "NA"));
    initList.addNodeInOrder(Creature("Gravane", 47, 47, 0, 15, 18, "NA"));

    std::cout << initList.listToString() << "\n";
    

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
                // if(exitBound.contains(mouseClick))
                if(exitButton.isClicked(mouseClick))
                {
                    return;
                }

                // if(nameText.isClicked(mouseClick))
                // {
                //     std::cout << nameText.getString() << "\n";
                // }
                // if(acText.isClicked(mouseClick))
                // {
                //     std::cout << acText.getString() << "\n";
                // }
            }

            window.clear(sf::Color::White);

            for(int i=0; i<6; i++)
            {
                window.draw(header[i]);
            }
            window.draw(exitButton);
            window.draw(exitButton.getText());
            // window.draw(nameText);
            // window.draw(nameText.getText());
            // window.draw(acText);
            // window.draw(acText.getText());
            window.display();
        }
    }
}