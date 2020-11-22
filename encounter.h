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

        void setPlayerPosition(sf::Vector2f pos);
        void setFont(const sf::Font &font);
        void setTexture(const sf::Texture &texture);

        // action functions
        void startInitiative();
        void calculateEncounterDifficulty();


    private:
        Initiative playerList;
        Initiative enemyList;
        Initiative initiativeList;

        int playerXpThreshhold[4];
        float enemyXpThreshhold;
        int encounterDifficulty;

        int threshholds[4][20];

        // helper functions
        void calculatePlayerXpThreshhold();
        void calculateEnemyXpThreshhold();
};

#endif