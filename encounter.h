#ifndef ENCOUNTER_H
#define ENCOUNTER_H

#include <fstream>
#include "initiativelist.h"

enum Difficulty {Easy, Medium, Hard, Deadly};

class Encounter
{
    public:
        Encounter();
        ~Encounter();

        // add to list/encounter
        void addPlayer(Creature player);
        void addEnemy(Creature enemy);

        // delete from list/encounter
        void deletePlayer();
        void deleteEnemy();

        // setters
        void setPlayerPosition(const sf::Vector2f &pos);
        void setEnemyPosition(const sf::Vector2f &pos);
        void setInitiativePosition(const sf::Vector2f &pos);
        void setFont(const sf::Font &font);
        void setTextTexture(const sf::Texture &texture);
        void setButtonTexture(const sf::Texture &texture);
        void setDifficultyTextPosition(const sf::Vector2f &pos);
        void setTotalEnemyXPTextPosition(const sf::Vector2f &pos);

        // getters
        std::string getEncounterDifficulty() const;
        std::string getTotalEnemyXP() const;

        // encounter actions
        void startInitiative();
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
        int encounterDifficulty;

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