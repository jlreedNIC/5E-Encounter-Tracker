#include "graphicsfunctions.h"


void initiativeGameLoop(sf::RenderWindow &window)
{
    Button exitButton("Exit");
    exitButton.setButtonPosition(50, 700);
    TextBox nameText("Rihala");
    nameText.setButtonPosition(50, 50);
    TextBox acText("13");
    acText.setButtonPosition(200, 50);

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

                if(nameText.isClicked(mouseClick))
                {
                    std::cout << nameText.getString() << "\n";
                }
                if(acText.isClicked(mouseClick))
                {
                    std::cout << acText.getString() << "\n";
                }
            }

            window.clear(sf::Color::White);
            window.draw(exitButton);
            window.draw(exitButton.getText());
            window.draw(nameText);
            window.draw(nameText.getText());
            window.draw(acText);
            window.draw(acText.getText());
            window.display();
        }
    }
}