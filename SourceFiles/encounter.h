/**
 * @file encounter.h
 * @author Jordan Reed
 * @brief Program to track encounters for D&D 5E
 * @date 2020-12-10
 * 
 */

#ifndef ENCOUNTER_H
#define ENCOUNTER_H

#include <fstream>
#include "initiativelist.h"

class Encounter
{
    public:
        // constructor and destructor
        Encounter();
        ~Encounter();

        std::string save(long unsigned int size);   // saves the player list and enemy list to a single file
        void load(const std::string &fileName);     // loads the player list and enemy list from a single file

        // add to list/encounter
        void addPlayer(Creature player);            // add a creature to the player list
        void addEnemy(Creature enemy);              // add a creature to the enemy list
        void addInitiative(Creature creature);      // add a creature to the initiative list

        // delete from list/encounter
        void deletePlayer(const sf::Vector2f &mouseClick);      // deletes a creature from the player list
        void deleteEnemy(const sf::Vector2f &mouseClick);       // deletes a creature from the enemy list
        void deleteInitiative(const sf::Vector2f &mouseClick);  // delete a creature from the initiative list

        void sort();    // sorts all 3 lists

        // setters
        void setPlayerPosition(const sf::Vector2f &pos);            // sets the position of the player list
        void setEnemyPosition(const sf::Vector2f &pos);             // sets the position of the enemy list
        void setInitiativePosition(const sf::Vector2f &pos);        // sets the position of the initiative list
        void setFont(const sf::Font &font);                         // sets the font for all lists
        void setTextTexture(const sf::Texture &texture);            // sets the texture used in all textboxes for the lists
        void setButtonTexture(const sf::Texture &texture);          // sets the texture for the buttons in the encounter
        void setDifficultyTextPosition(const sf::Vector2f &pos);    // sets the text position for encounter difficulty
        void setTotalEnemyXPTextPosition(const sf::Vector2f &pos);  // sets the text position for the total enemy XP
        void edit(const sf::Vector2f &mouseclick, const std::string &tempValue);    // updates a string at a specific position
        void editInitiative(const sf::Vector2f &mouseClick, const std::string &tempValue);  // updates a string in the initiative list

        void clearTextTexture();        // clears the textures used in the encounter

        // getters
        std::string getEncounterDifficulty() const;                 // gets the encounter difficulty in string format
        std::string getTotalEnemyXP() const;                        // gets the total enemy xp in string format
        std::string getString(sf::Vector2f &mouseClick);            // gets the string at a specific location
        std::string getInitiativeString(sf::Vector2f &mouseClick);  // gets the string from the initiative list at a specific location

        // boolean
        bool isClicked(const sf::Vector2f &mouseClick);             // checks to see if the player list or enemy list was clicked
        bool isClicked(const float &x, const float &y);             // checks to see if the player list or enemy list was clicked
        bool initIsClicked(const sf::Vector2f &mouseClick);         // checks to see if the initiative list was clicked
        bool playerAddClicked(const sf::Vector2f &mouseClick);      // checks to see if the add player button was clicked
        bool playerDeleteClicked(const sf::Vector2f &mouseClick);   // checks to see if the delete player pbutton was clicked
        bool enemyAddClicked(const sf::Vector2f &mouseClick);       // checks to see if the add enemy button was clicked
        bool enemyDeleteClicked(const sf::Vector2f &mouseClick);    // checks to see if the delete enemy button was clicked

        // encounter actions
        void startInitiative();                         // starts initiative and adds to the init. list from the player list and enemy list
        void advanceInitiative();                       // advances the turn to the next creature in initiative
        void endInitiative();                           // ends combat. resets the lists
        void calculateEncounterDifficulty();            // calculates the encounter difficulty based off of players and enemies
        void drawEncounter(sf::RenderWindow &window);   // draws the encounter to the screen
        void drawInitiative(sf::RenderWindow &window);  // draws the initiative to the screen

    private:
        Initiative playerList;          // holds the player creatures
        Initiative enemyList;           // holds the enemy creatures
        // make initList a pointer?
        // did not fix issue of init doesn't change original
        Initiative *initiativeList;      // holds the initiative order

        //buttons
        // make buttons dynamic?
        Button playerAdd;
        Button playerDelete;
        Button enemyAdd;
        Button enemyDelete;

        int playerXpThreshhold[4];      // holds the values for calculating encounter difficulty based off of players
        float enemyXpThreshhold;        // holds the value of calculated XP for enemies

        string difficulty;              // holds the difficulty text. Easy, medium, hard, or deadly
        sf::Text difficultyText;        // Text object for displaying the difficulty
        
        int totalEnemyXP;               // holds the sum of the enemies' XP
        sf::Text totalEnemyXPText;      // Text object for displaying the total XP

        int threshholds[4][20];         // table of info used in calculations

        // helper functions
        void calculatePlayerXpThreshhold();
        void calculateEnemyXpThreshhold();
        void setDifficulty();
};

#endif