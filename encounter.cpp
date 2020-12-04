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

    playerAdd.setString("+");
    playerDelete.setString("-");
    enemyAdd.setString("+");
    enemyDelete.setString("-");

    playerAdd.setButtonPosition(750, 50);
    playerDelete.setButtonPosition(750, 150);
    enemyAdd.setButtonPosition(750, 380);
    enemyDelete.setButtonPosition(750, 480);
}

Encounter::~Encounter()
{

}

void Encounter::addPlayer(Creature player)
{
    // add to playerList
    playerList.addNodeInOrder(player);
    clearTextTexture();
}

void Encounter::addEnemy(Creature enemy)
{
    // add to enemyList
    enemyList.addNodeInOrder(enemy);
    clearTextTexture();
}

void Encounter::addInitiative(Creature creature)
{
    initiativeList.addNodeInOrder(creature);
    clearTextTexture();
}

void Encounter::deletePlayer(const sf::Vector2f &mouseClick)
{
    sf::Vector2f currentPos = playerList.getPosition();
    playerList.deleteNode(mouseClick);
    playerList.setPosition(currentPos);
}

void Encounter::deleteEnemy(const sf::Vector2f &mouseClick)
{
    sf::Vector2f currentPos = enemyList.getPosition();
    enemyList.deleteNode(mouseClick);
    enemyList.setPosition(currentPos);
}

void Encounter::deleteInitiative(const sf::Vector2f &mouseClick)
{
    sf::Vector2f currentPos = initiativeList.getPosition();
    initiativeList.deleteNode(mouseClick);
    initiativeList.setPosition(currentPos);
}

void Encounter::sort()
{
    sf::Vector2f currentPos = playerList.getPosition();
    playerList.sort();
    playerList.setPosition(currentPos);

    currentPos = enemyList.getPosition();
    enemyList.sort();
    enemyList.setPosition(currentPos);

    
    currentPos = initiativeList.getPosition();
    initiativeList.sort();
    initiativeList.setPosition(currentPos);
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

void Encounter::setButtonTexture(const sf::Texture &texture)
{
    playerAdd.setTexture(texture);
    playerDelete.setTexture(texture);
    enemyAdd.setTexture(texture);
    enemyDelete.setTexture(texture);
}

void Encounter::edit(const sf::Vector2f &mouseClick, const std::string &tempValue)
{
    if(playerList.isNodeClicked(mouseClick))
        playerList.edit(mouseClick, tempValue);
    else if(enemyList.isNodeClicked(mouseClick))
        enemyList.edit(mouseClick, tempValue);
}

void Encounter::editInitiative(const sf::Vector2f &mouseClick, const std::string &tempValue)
{
    if(initiativeList.isNodeClicked(mouseClick))
        initiativeList.edit(mouseClick, tempValue);
}

void Encounter::clearTextTexture()
{
    playerList.clearTexture();
    enemyList.clearTexture();
    initiativeList.clearTexture();
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

std::string Encounter::getString(sf::Vector2f &mouseClick)
{
    if(playerList.isNodeClicked(mouseClick))
    {
        return playerList.getString(mouseClick);
    }
    else if(enemyList.isNodeClicked(mouseClick))
    {
        return enemyList.getString(mouseClick);
    }
    else return ""; // need to fix?
}

std::string Encounter::getInitiativeString(sf::Vector2f &mouseClick)
{
    std::string value;

    if(initiativeList.isNodeClicked(mouseClick))
        value = initiativeList.getString(mouseClick);
    
    return value;
}

bool Encounter::isClicked(const sf::Vector2f &mouseClick)
{
    return (playerList.isNodeClicked(mouseClick) ||
            enemyList.isNodeClicked(mouseClick));
}

bool Encounter::isClicked(const float &x, const float &y)
{
    return isClicked(sf::Vector2f(x, y));
}

bool Encounter::initIsClicked(const sf::Vector2f &mouseClick)
{
    return initiativeList.isNodeClicked(mouseClick);
}

bool Encounter::playerAddClicked(const sf::Vector2f &mouseClick)
{
    return playerAdd.isClicked(mouseClick);
}

bool Encounter::playerDeleteClicked(const sf::Vector2f &mouseClick)
{
    return playerDelete.isClicked(mouseClick);
}

bool Encounter::enemyAddClicked(const sf::Vector2f &mouseClick)
{
    return enemyAdd.isClicked(mouseClick);
}

bool Encounter::enemyDeleteClicked(const sf::Vector2f &mouseClick)
{
    return enemyDelete.isClicked(mouseClick);
}

void Encounter::startInitiative()
{
    playerList.sort();
    enemyList.sort();
    // start initiative
    initiativeList.clear();
    initiativeList.append(playerList);
    initiativeList.append(enemyList);

    initiativeList.setRoundIndicatorPosition();
}

void Encounter::calculateEncounterDifficulty()
{
    calculatePlayerXpThreshhold();
    calculateEnemyXpThreshhold();

    setDifficulty();
}

void Encounter::calculatePlayerXpThreshhold()
{
    std::string levels = playerList.getLevel();
    int playerSize = playerList.getSize();

    // get levels of players
    int *playerLevels = new int [playerSize];
    std::string::size_type sz;

    for(int i=0; i<playerSize; i++)
    {
        playerLevels[i] = stoi(levels, &sz);
        levels = levels.substr(sz);
    }

    // reinitialize xp threshholds
    for(int i=0; i<4; i++)
    {
        playerXpThreshhold[i] = 0;
    }
    // set xp threshholds for players
    for(int i=0; i<playerSize; i++)
    {
        for(int j=0; j<4; j++)
        {
            playerXpThreshhold[j] += threshholds[j][playerLevels[i]-1];
        }
    }

    delete [] playerLevels;
    
}

void Encounter::calculateEnemyXpThreshhold()
{
    int enemySize = enemyList.getSize();
    int playerSize = playerList.getSize();

    // get xp of enemies
    std::string tempCR = enemyList.getLevel();
    int *CR = new int [enemySize];
    std::string::size_type sz;
    
    for(int i=0; i<enemySize; i++)
    {
        CR[i] = stoi(tempCR, &sz);
        tempCR = tempCR.substr(sz);
    }
    
    enemyXpThreshhold = 0;
    // caclulate monster's xp threshhold
    for(int i=0; i<enemySize; i++)
        enemyXpThreshhold += CR[i];
    
    // set total monster xp
    totalEnemyXP = enemyXpThreshhold;

    // factor in monster multiplier based on number of monsters
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
    if(enemyXpThreshhold <= easy) difficulty = "EASY";
    else if(enemyXpThreshhold <= medium) difficulty = "MEDIUM";
    else if(enemyXpThreshhold <= hard) difficulty = "HARD";
    else difficulty = "DEADLY";
}

void Encounter::drawEncounter(sf::RenderWindow &window)
{
    playerList.drawList(window);
    enemyList.drawList(window);
    window.draw(playerAdd);
    window.draw(playerDelete);
    window.draw(enemyAdd);
    window.draw(enemyDelete);
}

void Encounter::drawInitiative(sf::RenderWindow &window)
{
    initiativeList.drawInitiativeList(window);
    window.draw(playerAdd);
    window.draw(playerDelete);
}