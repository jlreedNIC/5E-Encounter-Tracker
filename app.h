#ifndef APP_H
#define APP_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
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
        void editInitiative(sf::Event &event, bool &initClicked, sf::Vector2f &mouseClick, std::string &tempString);
        void initiativeDraw();

    private:
        sf::RenderWindow window;
        Encounter encounter;

        std::vector<std::string> saves;
        // sf::Text saves[3];  // change to vector of textboxes

        sf::Font headerFont;
        sf::Font buttonFont;
        
        sf::Texture buttonTexture;
        sf::Texture textBoxTexture;
        
        TextBox instructions;
        bool drawInstructions;

        // buttons
        Button newEncounter;
        Button loadEncounter;
        Button initiativeButton;
        Button exitButton;
        Button saveButton;
        Button startInitiative;
        Button sortButton;
        sf::Text headerText;

        // helper functions
        void mainMenuInput();
        void mainMenuUpdate();
        void mainMenuDraw();

        bool encounterInput();
        void encounterUpdate();
        void encounterDraw();
        //encounter headers
        sf::Text encounterTitles[3];
        sf::Text playerHeaders[7], enemyHeaders[7], encounterHeaders[2];
        sf::Text encounterDifficulty, totalXP;

        Creature newCreature;
        bool drawNewCreature;
        void editNewCreature(float x, float y);
        void editCreatureText(float x, float y);

        void editNewInitCreature(float x, float y);
        void editInitCreatureText(float x, float y);

        void loadSave();
        void newSave();

        void deleteEnemy();
        void deletePlayer();
        void deleteInitCreature();

        DiceRoller dice;
};

#endif