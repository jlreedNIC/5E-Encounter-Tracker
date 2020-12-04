#include "app.h"

App::App() : window(sf::VideoMode(800,800), "D&D 5E Encounter Tracker"), 
             encounter(), 
            //  newEncounter(), 
            //  loadEncounter(), 
            //  initiativeButton(),
            //  exitButton(),
            //  saveButton(),
             instructions("Not Implemented", buttonFont),
             headerText("Encounter Tracker", headerFont, 80), 
             encounterTitles{sf::Text("Players", buttonFont, 30), sf::Text("Enemies", buttonFont, 30), 
                             sf::Text("Encounter", buttonFont, 30)},
             playerHeaders{sf::Text("Name", buttonFont, 20), sf::Text("Init.", buttonFont, 20),
                           sf::Text("AC", buttonFont, 20), sf::Text("Health", buttonFont, 20),
                           sf::Text("Temp HP", buttonFont, 20),sf::Text("Status/Notes", buttonFont, 20),
                           sf::Text("Level", buttonFont, 20)},
             enemyHeaders{sf::Text("Name", buttonFont, 20), sf::Text("Initiative", buttonFont, 20),
                          sf::Text("AC", buttonFont, 20), sf::Text("Health", buttonFont, 20),
                          sf::Text("Temp HP", buttonFont, 20), sf::Text("Status/Notes", buttonFont, 20),
                          sf::Text("XP", buttonFont, 20)},
             encounterHeaders{sf::Text("Encounter Difficulty:", buttonFont, 20),
                              sf::Text("Total Encounter XP:", buttonFont, 20)},
             encounterDifficulty("EASY", buttonFont, 20),
             totalXP("0", buttonFont, 20)
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
    exitButton.setButtonPosition(50, 750);

    saveButton.createButton("save", buttonFont, buttonTexture);
    saveButton.setButtonPosition(250, 750);

    startInitiative.createButton("start initiative", buttonFont, buttonTexture);
    startInitiative.setButtonPosition(350, 750);

    sortButton.createButton("sort", buttonFont, buttonTexture);
    sortButton.setButtonPosition(150, 750);

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

    //setting font choices for encounter
    for(int i=0; i<3;i++)
    {
        encounterTitles[i].setFillColor(sf::Color::Black);
        encounterTitles[i].setStyle(sf::Text::Bold);
    }

    for(int i=0; i<7; i++)
    {
        playerHeaders[i].setFillColor(sf::Color::Black);
        enemyHeaders[i].setFillColor(sf::Color::Black);

        playerHeaders[i].setStyle(sf::Text::Bold);
        enemyHeaders[i].setStyle(sf::Text::Bold);
    }
    
    for(int i=0; i<2; i++)
    {
        encounterHeaders[i].setFillColor(sf::Color::Black);
        encounterHeaders[i].setStyle(sf::Text::Bold);
    }

    encounterDifficulty.setFillColor(sf::Color::Black);
    // encounterDifficulty.setStyle(sf::Text::Bold);

    totalXP.setFillColor(sf::Color::Black);
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
    drawInstructions = false;

    instructions.setTextBoxSize(sf::Vector2f(400, 100));
    instructions.setOutline();
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
        encounterUpdate();
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
                // FIX: this to return to main screen
                mainMenu();
                return;
            }

            // edit encounter
            if(encounter.isClicked(mouseClick))
            {
                // check if playerList or enemyList was clicked
                std::cout << "encounter clicked\n";
                editEncounter(mouseClick);
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

            // delete player
            if(encounter.playerDeleteClicked(mouseClick))
            {
                std::cout << "player to be deleted\n";
                instructions.setString("Click on the player you want to delete.");
                drawInstructions = true;
                deletePlayer();
            }

            // delete enemy
            if(encounter.enemyDeleteClicked(mouseClick))
            {
                std::cout << "enemy to be deleted\n";
                instructions.setString("Click on the enemy you want to delete.");
                drawInstructions = true;
                deleteEnemy();
            }

            // sort lists
            if(sortButton.isClicked(mouseClick))
            {
                encounter.sort();
            }

            // run encounter
            if(startInitiative.isClicked(mouseClick))
            {
                // start initiative order/run encounter
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
                    tempString = tempString.substr(0, size-2);
                    encounter.edit(mouseClick, tempString);
                    return;
                }

                encounter.edit(mouseClick, tempString);
            }

            encounterDraw();
        }
    }
}

void App::encounterUpdate()
{
    encounter.calculateEncounterDifficulty();
    encounterDifficulty.setString(encounter.getEncounterDifficulty());
    totalXP.setString(encounter.getTotalEnemyXP());

    encounter.sort();
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
    window.draw(sortButton);
    if(drawInstructions) window.draw(instructions);
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
                    tempString = tempString.substr(0, size-2);
                    newCreature.edit(pos, tempString);
                    return;
                }

                newCreature.edit(pos, tempString);
            }

            encounterDraw();
        }
    }
}

void App::deleteEnemy()
{
    std::cout << "delete enemy\n";
    instructions.setTextBoxPosition(50, 50);
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            // close window
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
            
            if(event.type == sf::Event::MouseButtonPressed)
            {
                std::cout << "mouse button pressed\n";
                float x = event.mouseButton.x;
                float y = event.mouseButton.y;
                sf::Vector2f mouseClick(x, y);

                if(encounter.isClicked(mouseClick))
                {
                    std::cout << "enemy clicked\n";
                    encounter.deleteEnemy(mouseClick);
                    drawInstructions = false;
                    return;
                }
                else return;
            }

            encounterDraw();
        }
    }
}

void App::deletePlayer()
{
    instructions.setTextBoxPosition(50, 380);
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            // close window
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
            
            if(event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f mouseClick(event.mouseButton.x, event.mouseButton.y);

                if(encounter.isClicked(mouseClick))
                {
                    encounter.deletePlayer(mouseClick);
                    drawInstructions = false;
                    return;
                }
                else return;
            }

            encounterDraw();
        }
    }
}

void App::initiative()
{
    encounter.startInitiative();
    encounter.setInitiativePosition(sf::Vector2f(50, 80));
    bool initClicked = false;
    std::string tempString;
    sf::Vector2f mouseClick;

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
                mouseClick = {posX, posY};
                if(exitButton.isClicked(mouseClick))
                {
                    encounter.startInitiative();
                    return;
                }

                // edits the initiative node
                if(encounter.initIsClicked(mouseClick))
                {
                    initClicked = true;
                    std::cout << "Node Clicked\n";
                    // gets the string to edit
                    tempString = encounter.getInitiativeString(mouseClick);
                    tempString += "|";
                    encounter.editInitiative(mouseClick, tempString);
                }

                // add creature to initiative
                if(encounter.playerAddClicked(mouseClick))
                {
                    // create new creature and add to player list
                    newCreature.setPosition(50, 80);
                    encounter.setInitiativePosition(sf::Vector2f(50, 115));

                    drawNewCreature = true;
                    editNewInitCreature(50, 80);
                    encounter.addInitiative(newCreature);
                    encounter.setInitiativePosition(sf::Vector2f(50, 80));
                    drawNewCreature = false;
                }

                // delete creature from initiative
                if(encounter.playerDeleteClicked(mouseClick))
                {
                    std::cout << "player to be deleted\n";
                    instructions.setString("Click on the creature you want to delete.");
                    drawInstructions = true;
                    deleteInitCreature();
                }

                // sort lists
                if(sortButton.isClicked(mouseClick))
                {
                    encounter.sort();
                }
            }

            if(initClicked)
            {
                editInitiative(event, initClicked, mouseClick, tempString);
            }

            initiativeDraw();
        }
    }
}

void App::editInitiative(sf::Event &event, bool &initClicked, sf::Vector2f &mouseClick, std::string &tempString)
{
    // while(window.pollEvent(event))
    // {
        // if click off of the node
        // FIX: these events are useless. the mouse button event
        // is entered into the main loop, not here
        if(event.type == sf::Event::MouseButtonPressed)
        {
            float posX = event.mouseButton.x;
            float posY = event.mouseButton.y;
            sf::Vector2f mouseClick2 = {posX, posY};

            if(exitButton.isClicked(mouseClick2))
            {
                tempString = tempString.substr(0, tempString.size()-1);
                encounter.editInitiative(mouseClick, tempString);
                initClicked = false;
                return;
            }

            if(mouseClick != mouseClick2)
            {
                std::cout << tempString << " ";
                tempString = tempString.substr(0, tempString.size()-1);
                std::cout << tempString << "\n";
                encounter.editInitiative(mouseClick, tempString);
                initClicked = false;
                return;
            }
        }

        // edit text
        if(event.type == sf::Event::TextEntered && initClicked)
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
                tempString = tempString.substr(0, size-2);
                encounter.editInitiative(mouseClick, tempString);
                initClicked = false;
                return;
            }

            encounter.editInitiative(mouseClick, tempString);
        }
    // }
}

void App::editNewInitCreature(float x, float y)
{
    editInitCreatureText(x, y);
    editInitCreatureText(x+100, y);
    editInitCreatureText(x+200, y);
    editInitCreatureText(x+250, y);
    editInitCreatureText(x+325, y);
    editInitCreatureText(x+425, y);
    editInitCreatureText(x+625, y);
}

void App::editInitCreatureText(float x, float y)
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
                    tempString = tempString.substr(0, size-2);
                    newCreature.edit(pos, tempString);
                    return;
                }

                newCreature.edit(pos, tempString);
            }

            initiativeDraw();
        }
    }
}

void App::deleteInitCreature()
{
    instructions.setTextBoxPosition(50, 380);
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            // close window
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
            
            if(event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f mouseClick(event.mouseButton.x, event.mouseButton.y);

                if(encounter.initIsClicked(mouseClick))
                {
                    encounter.deleteInitiative(mouseClick);
                    drawInstructions = false;
                    return;
                }
                else return;
            }

            initiativeDraw();
        }
    }
}

void App::initiativeDraw()
{
    window.clear(sf::Color::White);
    window.draw(exitButton);
    window.draw(sortButton);
    for(int i=0; i<7; i++)
    {
        window.draw(playerHeaders[i]);
    }
    encounter.drawInitiative(window);
    if(drawNewCreature) newCreature.draw(window);
    if(drawInstructions) window.draw(instructions);
    window.display();
}