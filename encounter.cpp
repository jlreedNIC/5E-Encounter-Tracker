#include "encounter.h"

Encounter::Encounter() : playerList(), enemyList(), initiativeList()
{
    for(int i=0; i<4; i++)
        playerXpThreshhold[i] = 0;
    enemyXpThreshhold = 0;
    encounterDifficulty = Difficulty::Easy;

    std::fstream in("threshholds", std::ios::in);
    for(int i=0; i<20; i++)
        for(int j=0; j<4; j++)
        {
            in >> threshholds[j][i];
        }
    
    in.close();
}

Encounter::~Encounter()
{

}

void Encounter::addPlayer(Creature player)
{
    // add to playerList
    playerList.addNodeInOrder(player);
}

void Encounter::addEnemy(Creature enemy)
{
    // add to enemyList
    enemyList.addNodeInOrder(enemy);
}

void Encounter::deletePlayer()
{
    // delete from playerList
}

void Encounter::deleteEnemy()
{

}

void Encounter::startInitiative()
{
    // start initiative
}

void Encounter::calculateEncounterDifficulty()
{
    calculatePlayerXpThreshhold();
    calculateEnemyXpThreshhold();

    std::cout << playerList.listToString() << "\n";
    std::cout << enemyList.listToString() << "\n";
    for(int i=0; i<4; i++)
    {
        std::cout << playerXpThreshhold[i] << " ";
    }
    std::cout << "\n" << enemyXpThreshhold << "\n";
}

void Encounter::calculatePlayerXpThreshhold()
{
    int playerSize = playerList.getSize();
    int *levels = new int [playerSize];

    levels = playerList.getLevel();

    //set player xp threshholds
    for(int i=0; i<playerSize; i++)
    {
        for(int j=0; j<4; j++)
        {
            playerXpThreshhold[j] += threshholds[j][levels[i] - 1];
        }
    }

    delete [] levels;
    
}

void Encounter::calculateEnemyXpThreshhold()
{
    int enemySize = enemyList.getSize();
    int playerSize = playerList.getSize();
    int *CR = new int [enemySize];

    CR = enemyList.getLevel();

    // caclulate monster's xp
    for(int i=0; i<enemySize; i++)
        enemyXpThreshhold += CR[i];

    float monsterMultipliers[8] = {.5, 1.0, 1.5, 2.0, 2.5, 3.0, 4.0, 4.0};
    int index = 0;

    if(enemySize == 1) index = 1;
    else if(enemySize == 2) index = 2;
    else if(enemySize < 7) index = 3;
    else if(enemySize < 11) index = 4;
    else if(enemySize < 15) index = 5;
    else if(enemySize > 14) index = 6;
    
    if(playerSize < 3) index++;
    else if(playerSize > 5) index--;

    enemyXpThreshhold *= monsterMultipliers[index];
}