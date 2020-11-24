#include "encounter.h"

Encounter::Encounter() : playerList(), enemyList(), initiativeList()
{
    for(int i=0; i<4; i++)
        playerXpThreshhold[i] = 0;
    enemyXpThreshhold = 0;
    encounterDifficulty = Difficulty::Easy;
    difficulty = "easy";
    totalEnemyXP = 0;

    std::fstream in("threshholds", std::ios::in);
    for(int i=0; i<20; i++)
        for(int j=0; j<4; j++)
        {
            in >> threshholds[j][i];
        }
    
    in.close();

    playerAdd.setString("add");
    playerDelete.setString("delete");
    enemyAdd.setString("add");
    enemyDelete.setString("delete");
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
    // delete from enemyList
}

void Encounter::setPlayerPosition(const sf::Vector2f &pos)
{
    playerList.setPosition(pos);
}

void Encounter::setEnemyPosition(const sf::Vector2f &pos)
{
    enemyList.setPosition(pos);
}

void Encounter::setInitiativePosition(const sf::Vector2f &pos)
{
    initiativeList.setPosition(pos);
}

void Encounter::setFont(const sf::Font &font)
{
    playerList.setListFont(font);
    enemyList.setListFont(font);
    initiativeList.setListFont(font);
    playerAdd.setFont(font);
    playerDelete.setFont(font);
    enemyAdd.setFont(font);
    enemyDelete.setFont(font);
}

void Encounter::setTextTexture(const sf::Texture &texture)
{
    playerList.setListTexture(texture);
    enemyList.setListTexture(texture);
    initiativeList.setListTexture(texture);
}

std::string Encounter::getEncounterDifficulty() const
{
    return difficulty;
}

std::string Encounter::getTotalEnemyXP() const
{
    std::ostringstream ostr;
    ostr << totalEnemyXP;
    return ostr.str();
}

void Encounter::startInitiative()
{
    // start initiative
    initiativeList.clear();
    initiativeList.append(playerList);
    initiativeList.append(enemyList);
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

    setDifficulty();
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
    
    totalEnemyXP = enemyXpThreshhold;

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
    delete [] CR;
}

void Encounter::setDifficulty()
{
    int easy = playerXpThreshhold[0];
    int medium = playerXpThreshhold[1];
    int hard = playerXpThreshhold[2];
    int deadly = playerXpThreshhold[3];

    easy = (medium + easy) / 2;
    medium = (hard + medium) / 2;
    hard = (deadly + hard) / 2;
    deadly = hard + 1;
    if(enemyXpThreshhold <= easy) difficulty = "easy";
    else if(enemyXpThreshhold <= medium) difficulty = "medium";
    else if(enemyXpThreshhold <= hard) difficulty = "hard";
    else difficulty = "deadly";
}

void Encounter::drawEncounter(sf::RenderWindow &window)
{
    playerList.drawList(window);
    enemyList.drawList(window);
}

void Encounter::drawInitiative(sf::RenderWindow &window)
{
    initiativeList.drawList(window);
}