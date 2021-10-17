/**
 * @file app.cpp
 * @author Jordan Reed
 * @brief Program to track encounters for D&D 5E
 * @date 2020-12-10
 * 
 */

/*
 * Need to fix code so it will scale the screen to fit each individual computer.
 * Also take code out to print to terminal.
 */

#include "app.h"

/**
 * @brief Construct a new App object. Sets the window, fonts and textures
 * 
 */
App::App() : window(sf::VideoMode(800,800), "D&D 5E Encounter Tracker"), 
             encounter(),
             instructions("Not Implemented", buttonFont),
             headerText("Encounter Tracker", headerFont, 80), 
             encounterTitles{sf::Text("Players", buttonFont, 30), sf::Text("Enemies", buttonFont, 30), 
                             sf::Text("Encounter", buttonFont, 30)},
             playerHeaders{sf::Text("Name", buttonFont, 20), sf::Text("Init.", buttonFont, 20),
                           sf::Text("AC", buttonFont, 20), sf::Text("Health", buttonFont, 20),
                           sf::Text("Temp HP", buttonFont, 20),sf::Text("Status/Notes", buttonFont, 20),
                           sf::Text("Level", buttonFont, 20)},
             enemyHeaders{sf::Text("Name", buttonFont, 20), sf::Text("Init.", buttonFont, 20),
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
    newEncounter.setPosition(300, 365);
    
    loadEncounter.createButton("load encounter", buttonFont, buttonTexture);
    loadEncounter.setPosition(300, 465);

    initiativeButton.createButton("initiative", buttonFont, buttonTexture);
    initiativeButton.setPosition(300, 265);

    exitButton.createButton("back", buttonFont, buttonTexture);
    exitButton.setPosition(50, 650);

    saveButton.createButton("save", buttonFont, buttonTexture);
    saveButton.setPosition(250, 650);

    startInitiative.createButton("start initiative", buttonFont, buttonTexture);
    startInitiative.setPosition(350, 650);

    sortButton.createButton("sort", buttonFont, buttonTexture);
    sortButton.setPosition(150, 650);

    // encounter save files
    std::fstream stream("Saves/encounter-saves", std::ios::in);
    if(!stream)
    {
        // no file created
        stream.open("Saves/encounter-saves", std::ios::out);
        stream.close();
    }
    else
    {
        //load saves from file
        while(!stream.eof())
        {
            std::string temp;
            getline(stream, temp);
            saves.push_back(temp);
        }
        stream.close();
        saves.pop_back();
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
    playerHeaders[1].setPosition(200, 45);
    playerHeaders[2].setPosition(250, 45);
    playerHeaders[3].setPosition(300, 45);
    playerHeaders[4].setPosition(375, 45);
    playerHeaders[5].setPosition(475, 45);
    playerHeaders[6].setPosition(675, 45);

    enemyHeaders[0].setPosition(50, 345);
    enemyHeaders[1].setPosition(200, 345);
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

/**
 * @brief Destroy the App object
 * 
 */
App::~App()
{
}

/**
 * @brief Checks to see if the window is still running
 * 
 * @return true If the window is still open
 * @return false If the window has been closed
 */
bool App::appIsOpen()
{
    return window.isOpen();
}

/**
 * @brief Main loop for main menu screen
 * 
 */
void App::mainMenu()
{
    while(appIsOpen())
    {
        //process input
        mainMenuInput();
        
        //render screen
        mainMenuDraw();  
    }
}

/**
 * @brief Handles the input on the main menu screen. Calls other functions based on user input.
 * 
 */
void App::mainMenuInput()
{
    sf::Event event;
    while(window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            window.close();
        }
        if(event.type == sf::Event::Resized)
        {
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            window.setView(sf::View(visibleArea));
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
                buildEncounter();
            }
            if(initiativeButton.isClicked(event.mouseButton.x, event.mouseButton.y))
            {
                //run initiative loop
                initiative();
            }
        }
    }
}

/**
 * @brief Draws the main menu to the window
 * 
 */
void App::mainMenuDraw()
{
    window.clear(sf::Color::White);
    window.draw(headerText);

    window.draw(newEncounter);
    window.draw(loadEncounter);
    window.draw(initiativeButton);
    window.display();
}

/**
 * @brief Handles the load save screen. Allows users to load a save file into the encounter builder.
 * 
 */
void App::loadSave()
{
    long unsigned int i;
    sf::Text instructions;
    instructions.setString("Click on the save file you want to load.\n(to be implemented)");
    instructions.setFont(buttonFont);
    instructions.setFillColor(sf::Color::Black);
    instructions.setCharacterSize(20);
    instructions.setPosition(120, 200);

    int size = saves.size();
    std::vector<TextBox> savesText;
    for(int j = 0; j < size; j++)
    {
        TextBox temp;
        temp.setString(saves[j]);
        savesText.push_back(temp);
    }

    for(i=0; i < saves.size(); i++)
    {
        savesText[i].setPosition(120, 240 + ((i+1)*35));
        savesText[i].setFont(buttonFont);
        savesText[i].setTextBoxSize(sf::Vector2f(100, 30));
    }

    std::string fileName;

    while(appIsOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if(event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
            else if(event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f mouseClick(event.mouseButton.x, event.mouseButton.y);
                std::cout << "mouse x: " << mouseClick.x << " " << event.mouseButton.x << "\n";
                std::cout << "mouse y: " << mouseClick.y << " " << event.mouseButton.y << "\n";
                // exit
                if(exitButton.isClicked(event.mouseButton.x, event.mouseButton.y))
                {
                    return;
                }
                
                // load file
                for(i=0; i < saves.size(); i++)
                {
                    if(savesText[i].isClicked(mouseClick)) 
                    {
                        fileName = saves[i];
                        std::cout << "save clicked\n";
                        encounter.load(fileName);
                        return;
                    }
                }
            }
        }

        // draw
        window.clear(sf::Color::White);
        window.draw(headerText);
        window.draw(instructions);
        for(i=0; i < saves.size(); i++)
            window.draw(savesText[i]);
        window.draw(exitButton);
        window.display();
    }
}

/**
 * @brief Saves the current encounter to a new file.
 * 
 */
void App::newSave()
{
    std::string saveFile;
    long unsigned int size = saves.size();
    saveFile = encounter.save(size);
    saves.push_back(saveFile);

    std::fstream file;
    file.open("Saves/encounter-saves", std::ios::out);
    for(long unsigned int i = 0; i < saves.size(); i++)
    {
        std::string temp = saves[i];
        file << temp << "\n";
    }
    file.close();

    instructions.setString("Encounter saved");
    instructions.setFont(buttonFont);
    instructions.setPosition(120, 200);
    drawInstructions = true;
}

/**
 * @brief Handles the main encounter screen and encounter loop
 * 
 */
void App::buildEncounter()
{
    encounter.setPlayerPosition(sf::Vector2f(50, 80));
    encounter.setEnemyPosition(sf::Vector2f(50, 380));
    encounter.setFont(buttonFont);

    encounter.calculateEncounterDifficulty();
    encounterDifficulty.setString(encounter.getEncounterDifficulty());
    totalXP.setString(encounter.getTotalEnemyXP());

    while(window.isOpen())
    {
        bool exitClicked = encounterInput();
        encounterUpdate();
        encounterDraw();

        if(exitClicked) return;
    }
}

/**
 * @brief Handles the input for the encounter screen. Will return a boolean value on whether or not the back button was clicked.
 * 
 * @return true If the back button is clicked.
 * @return false If the back button is not clicked.
 */
bool App::encounterInput()
{
    playerHeaders[0].setPosition(50, 45);
    playerHeaders[1].setPosition(200, 45);
    playerHeaders[2].setPosition(250, 45);
    playerHeaders[3].setPosition(300, 45);
    playerHeaders[4].setPosition(375, 45);
    playerHeaders[5].setPosition(475, 45);
    playerHeaders[6].setPosition(675, 45);
    startInitiative.setString("start initiative");

    bool exitClicked = false;

    sf::Event event;
    while(window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            window.close();
        }
        if(event.type == sf::Event::Resized)
        {
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            window.setView(sf::View(visibleArea));
        }
        if(event.type == sf::Event::MouseButtonPressed)
        {
            float posX = event.mouseButton.x;
            float posY = event.mouseButton.y;
            sf::Vector2f mouseClick = {posX, posY};
            drawInstructions = false;

            // exit to main menu
            if(exitButton.isClicked(mouseClick))
            {
                exitClicked = true;
            }

            // save encounter
            if(saveButton.isClicked(mouseClick))
            {
                std::cout << "saved\n";
                newSave();
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

                playerHeaders[0].setPosition(50, 45);
                playerHeaders[1].setPosition(200, 45);
                playerHeaders[2].setPosition(250, 45);
                playerHeaders[3].setPosition(300, 45);
                playerHeaders[4].setPosition(375, 45);
                playerHeaders[5].setPosition(475, 45);
                playerHeaders[6].setPosition(675, 45);
                startInitiative.setString("start initiative");
            }
        }
    }

    return exitClicked;
}

/**
 * @brief Allows the user to edit the content on the encounter screen.
 * 
 * @param mouseClick The location of a mouseclick (and string to edit)
 */
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

/**
 * @brief Updates the information on the encounter page, mainly the encounter difficulty and total XP
 * 
 */
void App::encounterUpdate()
{
    encounter.calculateEncounterDifficulty();
    encounterDifficulty.setString(encounter.getEncounterDifficulty());
    totalXP.setString(encounter.getTotalEnemyXP());

    encounter.sort();
}

/**
 * @brief Draws the encounter screen to the window
 * 
 */
void App::encounterDraw()
{
    sf::Text *header = new sf::Text;
    header->setString("Encounter");
    header->setFont(headerFont);
    header->setCharacterSize(40);
    header->setPosition(625, 2);
    header->setFillColor(sf::Color::Black);

    window.clear(sf::Color::White);
    window.draw(*header);
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
    delete header;
}

/**
 * @brief Edits a new creature object on the encounter screen
 * 
 * @param x X coordinate of the new creature object
 * @param y Y coordinate of the new creature object
 */
void App::editNewCreature(float x, float y)
{
    editCreatureText(x, y);
    editCreatureText(x+150, y);
    editCreatureText(x+200, y);
    editCreatureText(x+250, y);
    editCreatureText(x+325, y);
    editCreatureText(x+425, y);
    editCreatureText(x+625, y);
}

/**
 * @brief Edits a specific string of a new creature object on the encounter page
 * 
 * @param x X coordinate of the string to edit
 * @param y Y coordinate of the string to edit
 */
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
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || 
                   sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
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

/**
 * @brief Deletes a creature object from the enemy list on the encounter page. Handles input
 * 
 */
void App::deleteEnemy()
{
    std::cout << "delete enemy\n";
    instructions.setPosition(50, 50);
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

/**
 * @brief Deletes a creature object from the player list on the encounter page. Handles input.
 * 
 */
void App::deletePlayer()
{
    instructions.setPosition(50, 380);
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

// FIX: not urgent. split into init input
/**
 * @brief Handles the initiative screen. Starts initiative on the encounter currently built.
 * 
 */
void App::initiative()
{
    encounter.startInitiative();
    encounter.setInitiativePosition(sf::Vector2f(100, 80));
    startInitiative.setString("Next Turn");

    playerHeaders[0].setPosition(100, 45);
    playerHeaders[1].setPosition(250, 45);
    playerHeaders[2].setPosition(300, 45);
    playerHeaders[3].setPosition(350, 45);
    playerHeaders[4].setPosition(425, 45);
    playerHeaders[5].setPosition(525, 45);

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

            if(event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }

            if(event.type == sf::Event::MouseButtonPressed)
            {
                float posX = event.mouseButton.x;
                float posY = event.mouseButton.y;
                mouseClick = {posX, posY};

                // do these if statements need to be in this loop??
                // exit init
                if(exitButton.isClicked(mouseClick))
                {
                    encounter.endInitiative();
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
                    newCreature.setPosition(100, 80);
                    encounter.setInitiativePosition(sf::Vector2f(100, 115));

                    drawNewCreature = true;
                    editNewInitCreature(100, 80);
                    encounter.addInitiative(newCreature);
                    encounter.setInitiativePosition(sf::Vector2f(100, 80));
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

                // advance turn tracker
                if(startInitiative.isClicked(mouseClick))
                {
                    encounter.advanceInitiative();
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

/**
 * @brief Allows a user to edit a string on the initiative screen.
 * 
 * @param event The event that was polled in the input loop for initiative
 * @param initClicked Checks whether a node on the initiative screen was clicked, and if it's done being edited
 * @param mouseClick Location of string to be edited
 * @param tempString New string to update old string
 */
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

/**
 * @brief Edits a creature object on the initiative screen
 * 
 * @param x X coordinate of the creature
 * @param y Y coordinate of the creature
 */
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

/**
 * @brief Edits a specific string of a creature on the initiative screen
 * 
 * @param x X coordinate of the specific string
 * @param y Y coordinate of the specific string
 */
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

            if(event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
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

/**
 * @brief Handles deleting a creature object off the initiative screen
 * 
 */
void App::deleteInitCreature()
{
    instructions.setPosition(50, 380);
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

            if(event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
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

/**
 * @brief Draws the initiative screen to the window
 * 
 */
void App::initiativeDraw()
{
    sf::Text *header = new sf::Text;
    header->setString("Initiative");
    header->setFont(headerFont);
    header->setCharacterSize(40);
    header->setPosition(650, 2);
    header->setFillColor(sf::Color::Black);

    window.clear(sf::Color::White);
    window.draw(*header);
    window.draw(exitButton);
    window.draw(sortButton);
    window.draw(startInitiative);
    for(int i=0; i<6; i++)
    {
        window.draw(playerHeaders[i]);
    }
    encounter.drawInitiative(window);
    if(drawNewCreature) newCreature.draw(window);
    if(drawInstructions) window.draw(instructions);
    window.display();

    delete header;
}