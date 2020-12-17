/**
 * @file app.h
 * @author Jordan Reed
 * @brief Program to track encounters for D&D 5E
 * @date 2020-12-10
 * 
 */

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

        bool appIsOpen();       // checks to see if app/window is still running

        void mainMenu();        // starts the main menu

        void buildEncounter();  // starts the encounter screen
        void editEncounter(sf::Vector2f &mouseclick);   // allows a user to edit a string on the encounter screen

        void initiative();      // starts the initiative screen
        void editInitiative(sf::Event &event, bool &initClicked, sf::Vector2f &mouseClick, std::string &tempString);    // edits string on initiative
        void initiativeDraw();  // draws the initiative screen

    private:
        sf::RenderWindow window;
        Encounter encounter;

        std::vector<std::string> saves;

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
        void mainMenuInput();   // handles input on main menu screen
        void mainMenuDraw();    // draws the main menu screen

        bool encounterInput();  // handles input on encounter screen
        void encounterUpdate(); // updates the encounter screen
        void encounterDraw();   // draws the encounter screen
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