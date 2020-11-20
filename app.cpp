#include "app.h"

App::App() : window(sf::VideoMode(800,800), "D&D 5E Encounter Tracker"), 
            //  newEncounter(), 
             loadEncounter(), 
             initiativeButton(),
             exitButton(),
             headerText("Encounter Tracker", headerFont, 80)
{
    //window
    window.setPosition(sf::Vector2i(10, 30));

    // fonts
    headerFont.loadFromFile("Fonts/Sketch-Gothic-School.ttf");
    buttonFont.loadFromFile("Fonts/Roboto-Thin.ttf");

    // textures
    buttonTexture.loadFromFile("Textures/button.png");

    // header
    headerText.setFillColor(sf::Color::Black);
    headerText.setPosition(140,50);

    // buttons
    std::string temp = "New Encounter";
    newEncounter.createButton("New Encounter", buttonFont, buttonTexture);
    newEncounter.setButtonPosition(300, 365);
    
    loadEncounter.createButton("Load Encounter", buttonFont, buttonTexture);
    loadEncounter.setButtonPosition(300, 465);

    initiativeButton.createButton("Initiative", buttonFont, buttonTexture);
    initiativeButton.setButtonPosition(300, 265);

    exitButton.createButton("Exit", buttonFont, buttonTexture);
    exitButton.setButtonPosition(50, 700);

    std::fstream stream("encounter-saves", std::ios::in);
    if(!stream)
    {
        // no file created
        stream.open("encounter-saves", std::ios::out);
        stream.close();

        for(int i=0; i<3; i++)
            saves[i].setString("New File");
    }
    else
    {
        //load saves from file
        while(!stream.eof())
        {
            std::string temp;
            for(int i=0; i<3; i++)
            {
                getline(stream, temp);
                saves[i].setString(temp);
            }
        }
        stream.close();
    }

    for(int i=0; i<3; i++)
    {
        saves[i].setFont(buttonFont);
        saves[i].setCharacterSize(20);
        saves[i].setFillColor(sf::Color::Black);
    }
}

App::~App()
{
}

bool App::appIsOpen()
{
    return window.isOpen();
}

void App::mainMenu()
{
    while(appIsOpen())
    {
        //process input
        mainMenuInput();
        
        //update screen
        //not needed?
        mainMenuUpdate();
        
        //render screen
        mainMenuDraw();  
    }
}

void App::mainMenuInput()
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
            if(newEncounter.isClicked(event.mouseButton.x, event.mouseButton.y))
            {
                std::cout << "New Encounter\n";
                newSave();
            }
            if(loadEncounter.isClicked(event.mouseButton.x, event.mouseButton.y))
            {
                std::cout << "Load Encounter\n";
                loadSave();
            }
            if(initiativeButton.isClicked(event.mouseButton.x, event.mouseButton.y))
            {
                //run initiative loop
                initiative();
            }
        }
    }
}

void App::loadSave()
{
    sf::Text instructions;
    instructions.setString("Click on the save file you want to load.\n(to be implemented)");
    instructions.setFont(buttonFont);
    instructions.setFillColor(sf::Color::Black);
    instructions.setCharacterSize(20);
    instructions.setPosition(120, 200);

    for(int i=0; i<3; i++)
    {
        saves[i].setPosition(120, 240 + ((i+1)*25));
    }

    while(appIsOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if(event.type == sf::Event::MouseButtonPressed)
            {
                if(exitButton.isClicked(event.mouseButton.x, event.mouseButton.y))
                {
                    return;
                }
            }
        }

        // draw
        window.clear(sf::Color::White);
        window.draw(headerText);
        window.draw(instructions);
        for(int i=0; i<3; i++)
            window.draw(saves[i]);
        window.draw(exitButton);
        window.draw(exitButton.getText());
        window.display();
    }
}

void App::newSave()
{
    sf::Text instructions;
    instructions.setString("Click on where you want to save to.\n(to be implemented)");
    instructions.setFont(buttonFont);
    instructions.setFillColor(sf::Color::Black);
    instructions.setCharacterSize(20);
    instructions.setPosition(120, 200);

    for(int i=0; i<3; i++)
    {
        saves[i].setPosition(120, 240 + ((i+1)*25));
    }

    while(appIsOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if(event.type == sf::Event::MouseButtonPressed)
            {
                if(exitButton.isClicked(event.mouseButton.x, event.mouseButton.y))
                {
                    return;
                }
            }
        }

        // draw
        window.clear(sf::Color::White);
        window.draw(headerText);
        window.draw(instructions);
        for(int i=0; i<3; i++)
            window.draw(saves[i]);
        window.draw(exitButton);
        window.draw(exitButton.getText());
        window.display();
    }
}

void App::mainMenuUpdate()
{

}

void App::mainMenuDraw()
{
    window.clear(sf::Color::White);
    window.draw(headerText);

    window.draw(newEncounter);
    window.draw(newEncounter.getText());

    window.draw(loadEncounter);
    window.draw(loadEncounter.getText());

    window.draw(initiativeButton);
    window.draw(initiativeButton.getText());

    window.display();
}

void App::initiative()
{
    //game loop
        //input
        //update
        //render
    
    // Creature(string name, int maxHealth, int health, int tempHealth, int initiative, int armorClass, string status)
    Initiative initList;
    initList.addNodeInOrder(Creature("Rihala", 33, 33, 0, 1, 11, "NA"));
    initList.addNodeInOrder(Creature("Gravane", 47, 47, 0, 15, 18, "NA"));
    initList.setListFont(buttonFont);
    initList.setPosition(sf::Vector2f(50, 25));

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

            window.draw(exitButton);
            window.draw(exitButton.getText());
            initList.drawList(window);
            // window.draw(nameText);
            // window.draw(nameText.getText());
            // window.draw(acText);
            // window.draw(acText.getText());
            window.display();
        }
    }
}