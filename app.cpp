#include "app.h"

App::App() : window(sf::VideoMode(800,800), "D&D 5E Encounter Tracker"), 
             encounter(), 
            //  newEncounter(), 
            //  loadEncounter(), 
            //  initiativeButton(),
            //  exitButton(),
            //  saveButton(),
             headerText("Encounter Tracker", headerFont, 80)
             // add in encounter titles here
{
    //window
    window.setPosition(sf::Vector2i(10, 30));

    // fonts
    headerFont.loadFromFile("Fonts/Sketch-Gothic-School.ttf");
    buttonFont.loadFromFile("Fonts/Roboto-Thin.ttf");

    // textures
    buttonTexture.loadFromFile("Textures/dark-better-button3.png");
    textBoxTexture.loadFromFile("Textures/textBox.png");

    // header
    headerText.setFillColor(sf::Color::Black);
    headerText.setPosition(140,50);

    // buttons
    newEncounter.createButton("new encounter", buttonFont, buttonTexture);
    newEncounter.setButtonPosition(300, 365);
    
    loadEncounter.createButton("load encounter", buttonFont, buttonTexture);
    loadEncounter.setButtonPosition(300, 465);

    initiativeButton.createButton("initiative", buttonFont, buttonTexture);
    initiativeButton.setButtonPosition(300, 265);

    exitButton.createButton("back", buttonFont, buttonTexture);
    exitButton.setButtonPosition(50, 700);

    saveButton.createButton("save", buttonFont, buttonTexture);
    saveButton.setButtonPosition(150, 700);

    startInitiative.createButton("start initiative", buttonFont, buttonTexture);
    startInitiative.setButtonPosition(250, 700);

    // encounter save files
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

    encounter.setFont(buttonFont);
    encounter.setButtonTexture(buttonTexture);
    // setting titles for encounter
        encounterTitles[0].setString("Players");
        encounterTitles[1].setString("Enemies");
        encounterTitles[2].setString("Encounter");

        playerHeaders[0].setString("Name");
        enemyHeaders[0].setString("Name");

        playerHeaders[1].setString("Initiative");
        enemyHeaders[1].setString("Initiative");

        playerHeaders[2].setString("AC");
        enemyHeaders[2].setString("AC");

        playerHeaders[3].setString("Health");
        enemyHeaders[3].setString("Health");

        playerHeaders[4].setString("Temp HP");
        enemyHeaders[4].setString("Temp HP");

        playerHeaders[5].setString("Status/Notes");
        enemyHeaders[5].setString("Status/Notes");

        playerHeaders[6].setString("Level");
        enemyHeaders[6].setString("XP");

        encounterHeaders[0].setString("Encounter Difficulty:");
        encounterHeaders[1].setString("Total Encounter XP:");
    
    //setting font choices for encounter
    for(int i=0; i<3;i++)
    {
        encounterTitles[i].setFillColor(sf::Color::Black);
        encounterTitles[i].setFont(buttonFont);
        encounterTitles[i].setCharacterSize(30);
        encounterTitles[i].setStyle(sf::Text::Bold);
    }

    for(int i=0; i<7; i++)
    {
        playerHeaders[i].setFillColor(sf::Color::Black);
        enemyHeaders[i].setFillColor(sf::Color::Black);

        playerHeaders[i].setStyle(sf::Text::Bold);
        enemyHeaders[i].setStyle(sf::Text::Bold);

        playerHeaders[i].setFont(buttonFont);
        enemyHeaders[i].setFont(buttonFont);

        playerHeaders[i].setCharacterSize(20);
        enemyHeaders[i].setCharacterSize(20);
    }
    
    for(int i=0; i<2; i++)
    {
        encounterHeaders[i].setFillColor(sf::Color::Black);
        encounterHeaders[i].setFont(buttonFont);
        encounterHeaders[i].setCharacterSize(20);
        encounterHeaders[i].setStyle(sf::Text::Bold);
    }

    encounterDifficulty.setString("EASY");
        encounterDifficulty.setFillColor(sf::Color::Black);
        encounterDifficulty.setFont(buttonFont);
        encounterDifficulty.setCharacterSize(20);
        // encounterDifficulty.setStyle(sf::Text::Bold);

    totalXP.setString("0");
        totalXP.setFillColor(sf::Color::Black);
        totalXP.setFont(buttonFont);
        totalXP.setCharacterSize(20);
        // totalXP.setStyle(sf::Text::Bold);
    
    // set positions for encounter
    for(int i=0; i<3; i++)
    {
        encounterTitles[i].setPosition(30, 10 + (i*300));
    }
    playerHeaders[0].setPosition(50, 45);
    playerHeaders[1].setPosition(150, 45);
    playerHeaders[2].setPosition(250, 45);
    playerHeaders[3].setPosition(300, 45);
    playerHeaders[4].setPosition(375, 45);
    playerHeaders[5].setPosition(475, 45);
    playerHeaders[6].setPosition(675, 45);

    enemyHeaders[0].setPosition(50, 345);
    enemyHeaders[1].setPosition(150, 345);
    enemyHeaders[2].setPosition(250, 345);
    enemyHeaders[3].setPosition(300, 345);
    enemyHeaders[4].setPosition(375, 345);
    enemyHeaders[5].setPosition(475, 345);
    enemyHeaders[6].setPosition(675, 345);

    encounterHeaders[0].setPosition(50, 645);
    encounterHeaders[1].setPosition(50, 675);

    encounterDifficulty.setPosition(300, 645);
    totalXP.setPosition(300, 675);

    newCreature.setFont(buttonFont);
    newCreature.setTexture(textBoxTexture);

    drawNewCreature = false;
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
                buildEncounter();
                // newSave();
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

void App::mainMenuUpdate()
{

}

void App::mainMenuDraw()
{
    window.clear(sf::Color::White);
    window.draw(headerText);

    window.draw(newEncounter);
    window.draw(loadEncounter);
    window.draw(initiativeButton);
    window.display();
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

void App::buildEncounter()
{
    // creature(string name, maxhealth, health, temphealth, initiative, armorclass, string status, level/cr);
    encounter.addPlayer(Creature("Rihala", 33, 33, 24, dice.rollDice(20), 11, "bear form", 4));
    encounter.addPlayer(Creature("Garth", 47, 47, 0, dice.rollDice(20), 14, "raging", 4));
    encounter.addPlayer(Creature("Gravane", 37, 5, 0, dice.rollDice(20), 18, "bleeding out", 4));
    encounter.addPlayer(Creature("Robinton", 30, 30, 0, dice.rollDice(20), 13, "NA", 4));
    encounter.addEnemy(Creature("Spectator", 39, 39, 0, dice.rollDice(20, 2), 14, "NA", 700));
    encounter.addEnemy(Creature("Bugbear", 27, 27, 0, dice.rollDice(20), 16, "NA", 200));
    encounter.setPlayerPosition(sf::Vector2f(50, 80));
    encounter.setEnemyPosition(sf::Vector2f(50, 380));
    encounter.setFont(buttonFont);

    encounter.calculateEncounterDifficulty();
    encounterDifficulty.setString(encounter.getEncounterDifficulty());
    totalXP.setString(encounter.getTotalEnemyXP());

    while(window.isOpen())
    {
        encounterInput();
        encounterProcess();
        encounterDraw();
    }
}

void App::encounterInput()
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

            // exit to main menu
            if(exitButton.isClicked(mouseClick))
            {
                // fix this to return to main screen
                mainMenu();
                return;
            }

            // edit encounter
            if(encounter.isClicked(mouseClick))
            {
                // check if somewhere on the encounter was clicked
                std::cout << "encounter clicked\n";
                editEncounter(mouseClick);

                // update encounter
                encounter.calculateEncounterDifficulty();
                encounterDifficulty.setString(encounter.getEncounterDifficulty());
                totalXP.setString(encounter.getTotalEnemyXP());
            }

            // add player
            if(encounter.playerAddClicked(mouseClick))
            {
                // create new creature and add to player list
                newCreature.setPosition(50, 80);
                encounter.setPlayerPosition(sf::Vector2f(50, 115));

                drawNewCreature = true;
                editNewCreature(50, 80);
                encounter.addPlayer(newCreature);
                encounter.setPlayerPosition(sf::Vector2f(50, 80));
                drawNewCreature = false;
            }
            
            // add enemy
            if(encounter.enemyAddClicked(mouseClick))
            {
                // create new creature and add to enemy list
                newCreature.setPosition(50, 380);
                encounter.setEnemyPosition(sf::Vector2f(50, 415));

                drawNewCreature = true;
                editNewCreature(50, 380);
                encounter.addEnemy(newCreature);
                encounter.setEnemyPosition(sf::Vector2f(50, 380));
                drawNewCreature = false;
            }

            // run encounter
            if(startInitiative.isClicked(mouseClick))
            {
                // start initiative order/run encounter
                encounter.startInitiative();
                initiative();
            }
        }
    }
}

void App::editEncounter(sf::Vector2f &mouseClick)
{
    // get string to edit
    std::string tempString = encounter.getString(mouseClick);
    tempString += "|";
    encounter.edit(mouseClick, tempString);

    sf::Event event;
    while(window.isOpen())
    {
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
                sf::Vector2f mouseClick2 = {posX, posY};

                if(exitButton.isClicked(mouseClick2))
                {
                    tempString = tempString.substr(0, tempString.size()-1);
                    encounter.edit(mouseClick, tempString);
                    return;
                }

                if(mouseClick != mouseClick2)
                {
                    tempString = tempString.substr(0, tempString.size()-1);
                    encounter.edit(mouseClick, tempString);
                    return;
                }
            }

            if(event.type == sf::Event::TextEntered)
            {
                // get rid of cursor
                tempString = tempString.substr(0, tempString.size()-1);
                // add new text
                tempString += event.text.unicode;
                // add cursor back
                tempString += "|";

                // size of tempString
                unsigned int size = tempString.size();

                // if backspace pressed
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
                {
                    tempString = tempString.substr(0, size-3);
                    tempString += "|";
                }

                // if enter pressed
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                {
                    tempString = tempString.substr(0, size-1);
                    encounter.edit(mouseClick, tempString);
                    return;
                }

                encounter.edit(mouseClick, tempString);
            }

            encounterDraw();
        }
    }
}

void App::encounterProcess()
{

}

void App::encounterDraw()
{
    window.clear(sf::Color::White);
    for(int i=0; i<3; i++)
    {
        window.draw(encounterTitles[i]);
    }
    for(int i=0; i<7; i++)
    {
        window.draw(playerHeaders[i]);
        window.draw(enemyHeaders[i]);
    }
    for(int i=0; i<2; i++)
    {
        window.draw(encounterHeaders[i]);
    }
    window.draw(encounterDifficulty);
    window.draw(totalXP);
    if(drawNewCreature) newCreature.draw(window);
    encounter.drawEncounter(window);
    window.draw(exitButton);
    window.draw(saveButton);
    window.draw(startInitiative);
    window.display();
}

void App::editNewCreature(float x, float y)
{
    editCreatureText(x, y);
    editCreatureText(x+100, y);
    editCreatureText(x+200, y);
    editCreatureText(x+250, y);
    editCreatureText(x+325, y);
    editCreatureText(x+425, y);
    editCreatureText(x+625, y);
}

void App::editCreatureText(float x, float y)
{
    // get string to edit
    sf::Vector2f pos(x, y);
    std::string tempString = newCreature.getString(pos);
    tempString += "|";
    newCreature.edit(pos, tempString);

    sf::Event event;
    while(window.isOpen())
    {
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
                sf::Vector2f mouseClick2 = {posX, posY};

                if(exitButton.isClicked(mouseClick2))
                {
                    tempString = tempString.substr(0, tempString.size()-1);
                    newCreature.edit(pos, tempString);
                    return;
                }

                if(pos != mouseClick2)
                {
                    tempString = tempString.substr(0, tempString.size()-1);
                    newCreature.edit(pos, tempString);
                    return;
                }
            }

            if(event.type == sf::Event::TextEntered)
            {
                // get rid of cursor
                tempString = tempString.substr(0, tempString.size()-1);
                // add new text
                tempString += event.text.unicode;
                // add cursor back
                tempString += "|";

                // size of tempString
                unsigned int size = tempString.size();

                // if backspace pressed
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
                {
                    tempString = tempString.substr(0, size-3);
                    tempString += "|";
                }

                // if enter pressed
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                {
                    tempString = tempString.substr(0, size-1);
                    newCreature.edit(pos, tempString);
                    return;
                }

                newCreature.edit(pos, tempString);
            }

            encounterDraw();
        }
    }
}

void App::initiative()
{
    //game loop
        //input
        //update
        //render
    // encounter.startInitiative();
    // Creature(string name, int maxHealth, int health, int tempHealth, int initiative, int armorClass, string status)
    // Initiative initList;
    // initList.addNodeInOrder(Creature("Rihala", 33, 33, 0, 1, 11, "NA", 4));
    // initList.addNodeInOrder(Creature("Gravane", 47, 47, 0, 15, 18, "NA", 4));
    // initList.setListFont(buttonFont);
    // initList.setPosition(sf::Vector2f(50, 25));

    // encounter.addPlayer(Creature("Rihala", 33, 33, 0, 1, 11, "raging", 4));
    // encounter.addPlayer(Creature("Gravane", 47, 47, 0, 15, 18, "NA", 4));
    // encounter.addEnemy(Creature("Goblin Fighter", 30, 30, 0, 5, 15, "NA", 50));
    // encounter.addEnemy(Creature("Kobold", 0, 12, 0, 20, 13, "Bleeding out", 25));

    // encounter.calculateEncounterDifficulty();

    // std::cout << initList.listToString() << "\n";
    encounter.setInitiativePosition(sf::Vector2f(50, 80));

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

                if(encounter.initIsClicked(mouseClick))
                {
                    std::cout << "Node Clicked\n";
                    // editNode(initList, posX, posY);
                    // initList.edit(posX, posY);
                }
            }

            window.clear(sf::Color::White);

            window.draw(exitButton);
            window.draw(exitButton.getText());
            for(int i=0; i<7; i++)
            {
                window.draw(playerHeaders[i]);
            }
            encounter.drawInitiative(window);
            window.display();
        }
    }
}

void App::editNode(Initiative &initList, const float &x, const float &y)
{
    // sf::Event event;
    // TextBox textbox = initList.getTextBox(x, y);
    // sf::Vector2f pos(x, y);
    // std::string tempString = initList.getString(pos);
    // tempString += "|";
    // initList.edit(x, y, tempString);

    // while(window.isOpen())
    // {
    //     while(window.pollEvent(event))
    //     {
    //         if(event.type == sf::Event::Closed)
    //         {
    //             window.close();
    //         }

    //         if(event.type == sf::Event::MouseButtonPressed)
    //         {
    //             float posX = event.mouseButton.x;
    //             float posY = event.mouseButton.y;
    //             sf::Vector2f mouseClick = {posX, posY};
    //             if(exitButton.isClicked(mouseClick))
    //             {
    //                 tempString = tempString.substr(0, tempString.size()-1);
    //                 initList.edit(x, y, tempString);
    //                 return;
    //             }

    //             if(!textbox.isClicked(posX, posY))
    //             {
    //                 tempString = tempString.substr(0, tempString.size()-1);
    //                 initList.edit(x, y, tempString);
    //                 return;
    //             }
    //         }

    //         if (event.type == sf::Event::TextEntered)
    //         {
    //             tempString = tempString.substr(0, tempString.size()-1);
    //             tempString += event.text.unicode;
    //             tempString += "|";
    //             unsigned int size = tempString.size();

    //             if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
    //             {
    //                 tempString = tempString.substr(0, size-3);
    //                 tempString += "|";
    //             }
    //             if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    //                 {
    //                     tempString = tempString.substr(0, tempString.size()-1);
    //                     initList.edit(x, y, tempString);
    //                     return;
    //                 }
                
    //             initList.edit(x, y, tempString);
    //         }

    //         window.clear(sf::Color::White);
    //         window.draw(exitButton);
    //         initList.drawList(window);
    //         window.display();
    //     }
    // }
}