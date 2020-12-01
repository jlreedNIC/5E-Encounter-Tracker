#ifndef APP_H
#define APP_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include "button.h"
#include "textbox.h"
#include "initiativelist.h"
#include "encounter.h"
#include "diceroll.h"

class App
{
    public:
        App();
        ~App();

        bool appIsOpen();

        void mainMenu();

        void buildEncounter();
        void editEncounter(sf::Vector2f &mouseclick);

        void initiative();
        void editNode(Initiative& initList, const float &x, const float &y);

    private:
        sf::RenderWindow window;
        Encounter encounter;

        sf::Text saves[3];  // change to textbox

        sf::Font headerFont;
        sf::Font buttonFont;
        
        sf::Texture buttonTexture;

        // buttons
        Button newEncounter;
        Button loadEncounter;
        Button initiativeButton;
        Button exitButton;
        sf::Text headerText;

        // helper functions
        void mainMenuInput();
        void mainMenuUpdate();
        void mainMenuDraw();

        void encounterInput();
        void encounterProcess();
        void encounterDraw();
        //encounter headers
        sf::Text encounterTitles[3];
        sf::Text playerHeaders[7], enemyHeaders[7], encounterHeaders[2];
        sf::Text encounterDifficulty, totalXP;

        void loadSave();
        void newSave();

        DiceRoller dice;
};

#endif