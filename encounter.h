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
        Encounter();
        ~Encounter();

        std::string save(long unsigned int size);
        void load(const std::string &fileName);

        // add to list/encounter
        void addPlayer(Creature player);
        void addEnemy(Creature enemy);
        void addInitiative(Creature creature);

        // delete from list/encounter
        void deletePlayer(const sf::Vector2f &mouseClick);
        void deleteEnemy(const sf::Vector2f &mouseClick);
        void deleteInitiative(const sf::Vector2f &mouseClick);

        void sort();

        // setters
        void setPlayerPosition(const sf::Vector2f &pos);
        void setEnemyPosition(const sf::Vector2f &pos);
        void setInitiativePosition(const sf::Vector2f &pos);
        void setFont(const sf::Font &font);
        void setTextTexture(const sf::Texture &texture);
        void setButtonTexture(const sf::Texture &texture);
        void setDifficultyTextPosition(const sf::Vector2f &pos);
        void setTotalEnemyXPTextPosition(const sf::Vector2f &pos);
        void edit(const sf::Vector2f &mouseclick, const std::string &tempValue);
        void editInitiative(const sf::Vector2f &mouseClick, const std::string &tempValue);

        void clearTextTexture();

        // getters
        std::string getEncounterDifficulty() const;
        std::string getTotalEnemyXP() const;
        std::string getString(sf::Vector2f &mouseClick);
        std::string getInitiativeString(sf::Vector2f &mouseClick);

        // boolean
        bool isClicked(const sf::Vector2f &mouseClick);
        bool isClicked(const float &x, const float &y);
        bool initIsClicked(const sf::Vector2f &mouseClick);
        bool playerAddClicked(const sf::Vector2f &mouseClick);
        bool playerDeleteClicked(const sf::Vector2f &mouseClick);
        bool enemyAddClicked(const sf::Vector2f &mouseClick);
        bool enemyDeleteClicked(const sf::Vector2f &mouseClick);

        // encounter actions
        void startInitiative();
        void advanceInitiative();
        void endInitiative();
        void calculateEncounterDifficulty();
        void drawEncounter(sf::RenderWindow &window);
        void drawInitiative(sf::RenderWindow &window);

    private:
        Initiative playerList;
        Initiative enemyList;
        Initiative initiativeList;

        //buttons
        Button playerAdd;
        Button playerDelete;
        Button enemyAdd;
        Button enemyDelete;

        int playerXpThreshhold[4];
        float enemyXpThreshhold;

        string difficulty;
        sf::Text difficultyText;
        
        int totalEnemyXP;
        sf::Text totalEnemyXPText;

        int threshholds[4][20];

        // helper functions
        void calculatePlayerXpThreshhold();
        void calculateEnemyXpThreshhold();
        void setDifficulty();
};

#endif