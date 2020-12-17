/**
 * @file encounter.h
 * @author Jordan Reed
 * @brief Program to track encounters for D&D 5E
 * @date 2020-12-10
 * 
 */

#include "encounter.h"

/**
 * @brief Construct a new Encounter. Calls constructors for 3 different lists. Initializes data table and buttons.
 * 
 */
Encounter::Encounter() : playerList(), enemyList()
{
    for(int i=0; i<4; i++)
        playerXpThreshhold[i] = 0;
    enemyXpThreshhold = 0;
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

    playerAdd.setPosition(750, 50);
    playerDelete.setPosition(750, 150);
    enemyAdd.setPosition(750, 380);
    enemyDelete.setPosition(750, 480);

    initiativeList = new Initiative;
}

/**
 * @brief Destroy the Encounter object
 * 
 */
Encounter::~Encounter()
{
    delete initiativeList;
}

/**
 * @brief Saves the encounter and returns the filename it is saved under, for use in the main save file.
 * 
 * @param size How many encounters are already in the save file.
 * @return std::string File name the current encounter is saved under
 */
std::string Encounter::save(long unsigned int size)
{
    std::ostringstream ostr;
    std::fstream file;

    ostr << "Encounter" << size + 1 << "-" << playerList.getFirstName() << "-" << enemyList.getFirstName() << "-" << totalEnemyXP;

    file.open("Saves/" + ostr.str() + ".csv", std::ios::out);
    playerList.save(file);
    file << "*\n";
    enemyList.save(file);
    file.close();

    return ostr.str();
}

/**
 * @brief Loads the encounter into the player list and enemy list.
 * 
 * @param fileName String that contains the name of the file to open
 */
void Encounter::load(const std::string &fileName)
{
    playerList.clear();
    enemyList.clear();
    initiativeList->clear();

    std::fstream file;
    file.open("Saves/" + fileName + ".csv", std::ios::in);

    if(!file)
    {
        std::cerr << "Error opening file.\n";
        exit(0); // FIX: change to exception handling try/catch block
    }

    playerList.load(file);
    enemyList.load(file);

    file.close();
    enemyList.deleteLast();

    std::cout << playerList.listToString() << "\n";
    std::cout << enemyList.listToString() << "\n";
}

/**
 * @brief Adds a creature object to the player list and clears the temporary texture
 *        from all nodes.
 * 
 * @param player Creature to be added
 */
void Encounter::addPlayer(Creature player)
{
    // add to playerList
    playerList.addNodeInOrder(player);
    clearTextTexture();
}

/**
 * @brief Adds a creature to the enemy list and clears the temporary texture
 *        from all nodes.
 * 
 * @param enemy Creature to be added
 */
void Encounter::addEnemy(Creature enemy)
{
    // add to enemyList
    enemyList.addNodeInOrder(enemy);
    clearTextTexture();
}

/**
 * @brief Adds a creature to the initiative list and clears the temporary
 *        texture from all nodes
 * 
 * @param creature Creature to be added
 */
void Encounter::addInitiative(Creature creature)
{
    initiativeList->addNodeInOrder(creature);
    clearTextTexture();
}

/**
 * @brief Deletes a player from the player list. Searches for the correct player based off of position.
 *        Resets the positions of all nodes after one node is deleted.
 * 
 * @param mouseClick Position to search for.
 */
void Encounter::deletePlayer(const sf::Vector2f &mouseClick)
{
    sf::Vector2f currentPos = playerList.getPosition();
    playerList.deleteNode(mouseClick);
    playerList.setPosition(currentPos);
}

/**
 * @brief Deletes an enemy from the enemy list. Searches for the correct creature based off of position.
 *        Resets the positions of all nodes after one node is deleted.
 * 
 * @param mouseClick Position to search for.
 */
void Encounter::deleteEnemy(const sf::Vector2f &mouseClick)
{
    sf::Vector2f currentPos = enemyList.getPosition();
    enemyList.deleteNode(mouseClick);
    enemyList.setPosition(currentPos);
}

/**
 * @brief Deletes a creature from the initiative list. Searches for the correct creature based off of position.
 *        Resets the positions of all nodes after one node is deleted.
 * 
 * @param mouseClick Position to search for.
 */
void Encounter::deleteInitiative(const sf::Vector2f &mouseClick)
{
    sf::Vector2f currentPos = initiativeList->getPosition();
    initiativeList->deleteNode(mouseClick);
    initiativeList->setPosition(currentPos);
}

/**
 * @brief Sorts the player list, enemy list, and initiative list, while keeping the initial position.
 * 
 */
void Encounter::sort()
{
    sf::Vector2f currentPos = playerList.getPosition();
    playerList.sort();
    playerList.setPosition(currentPos);

    currentPos = enemyList.getPosition();
    enemyList.sort();
    enemyList.setPosition(currentPos);

    currentPos = initiativeList->getPosition();
    initiativeList->sort();
    initiativeList->setPosition(currentPos);
}

/**
 * @brief Sets the position of the player list.
 * 
 * @param pos Position to set the player list to
 */
void Encounter::setPlayerPosition(const sf::Vector2f &pos)
{
    playerList.setPosition(pos);
}

/**
 * @brief Sets the position of the enemy list.
 * 
 * @param pos Position to set the enemy list to.
 */
void Encounter::setEnemyPosition(const sf::Vector2f &pos)
{
    enemyList.setPosition(pos);
}

/**
 * @brief Sets the position of the initiative list.
 * 
 * @param pos Position to set the initiative list to
 */
void Encounter::setInitiativePosition(const sf::Vector2f &pos)
{
    initiativeList->setPosition(pos);
}

/**
 * @brief Sets the font for all the lists and buttons in the encounter.
 * 
 * @param font Font to be used
 */
void Encounter::setFont(const sf::Font &font)
{
    playerList.setListFont(font);
    enemyList.setListFont(font);
    initiativeList->setListFont(font);
    playerAdd.setFont(font);
    playerDelete.setFont(font);
    enemyAdd.setFont(font);
    enemyDelete.setFont(font);
}

/**
 * @brief Sets the texture for all the lists in the encounter.
 * 
 * @param texture Texture to be used. No default value
 */
void Encounter::setTextTexture(const sf::Texture &texture)
{
    playerList.setListTexture(texture);
    enemyList.setListTexture(texture);
    initiativeList->setListTexture(texture);
}

/**
 * @brief Sets the texture for all the buttons in the encounter.
 * 
 * @param texture Texture to be used. No default value
 */
void Encounter::setButtonTexture(const sf::Texture &texture)
{
    playerAdd.setTexture(texture);
    playerDelete.setTexture(texture);
    enemyAdd.setTexture(texture);
    enemyDelete.setTexture(texture);
}

/**
 * @brief Updates the string of either the player list or enemy list based off of its position.
 * 
 * @param mouseClick Position of string to edit
 * @param tempValue Value of new string
 */
void Encounter::edit(const sf::Vector2f &mouseClick, const std::string &tempValue)
{
    if(playerList.isNodeClicked(mouseClick))
        playerList.edit(mouseClick, tempValue);
    else if(enemyList.isNodeClicked(mouseClick))
        enemyList.edit(mouseClick, tempValue);
}

/**
 * @brief Updates the string of the initiative list based off of its position.
 * 
 * @param mouseClick Position of string to edit
 * @param tempValue Value of new string
 */
void Encounter::editInitiative(const sf::Vector2f &mouseClick, const std::string &tempValue)
{
    if(initiativeList->isNodeClicked(mouseClick))
        initiativeList->edit(mouseClick, tempValue);
}

/**
 * @brief Clears the texture from all three lists.
 * 
 */
void Encounter::clearTextTexture()
{
    playerList.clearTexture();
    enemyList.clearTexture();
    initiativeList->clearTexture();
}

/**
 * @brief Gets the encounter difficulty
 * 
 * @return std::string Copy of the encounter difficulty
 */
std::string Encounter::getEncounterDifficulty() const
{
    return difficulty;
}

/**
 * @brief Gets the sum of all enemies' XP in string format
 * 
 * @return std::string Contains a copy of the string containing the sum of all enemies' XP
 */
std::string Encounter::getTotalEnemyXP() const
{
    std::ostringstream ostr;
    ostr << totalEnemyXP;
    return ostr.str();
}

/**
 * @brief Gets the string from either the player list or enemy list based off of its position.
 *        If the mouse click is not in either list, it returns an empty string.
 * 
 * @param mouseClick Position of the desired string to get
 * @return std::string A copy of a string at a given position, or an empty string.
 */
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

/**
 * @brief Gets the string from the initiative list based off of its position. If the mouse
 *        click is not in the list, it returns an empty string.
 * 
 * @param mouseClick 
 * @return std::string 
 */
std::string Encounter::getInitiativeString(sf::Vector2f &mouseClick)
{
    std::string value;

    if(initiativeList->isNodeClicked(mouseClick))
        value = initiativeList->getString(mouseClick);
    
    return value;
}

/**
 * @brief Checks to see if the enemy list or player list has been clicked
 * 
 * @param mouseClick Location of the mouse click
 * @return true If a node on one of the lists was clicked
 * @return false If no node on one of the lists was clicked
 */
bool Encounter::isClicked(const sf::Vector2f &mouseClick)
{
    return (playerList.isNodeClicked(mouseClick) ||
            enemyList.isNodeClicked(mouseClick));
}

/**
 * @brief Checks to see if the enemy list or player list has been clicked
 * 
 * @param x X coordinate of the mouse click
 * @param y Y coordinate of the mouse click
 * @return true If a node on one of the lists was clicked
 * @return false If no node on one of the lists was clicked
 */
bool Encounter::isClicked(const float &x, const float &y)
{
    return isClicked(sf::Vector2f(x, y));
}

/**
 * @brief Checks to see if the initiative list was clicked
 * 
 * @param mouseClick Location of the mouse click
 * @return true If a node on the init. list was clicked
 * @return false If all nodes on the inti. list were not clicked
 */
bool Encounter::initIsClicked(const sf::Vector2f &mouseClick)
{
    return initiativeList->isNodeClicked(mouseClick);
}

/**
 * @brief Checks to see if the button handling adding a player was clicked
 * 
 * @param mouseClick Location of the mouse click
 * @return true If the player add button was clicked
 * @return false If the player add button was not clicked
 */
bool Encounter::playerAddClicked(const sf::Vector2f &mouseClick)
{
    return playerAdd.isClicked(mouseClick);
}

/**
 * @brief Checks to see if the button handling deleting a player was clicked
 * 
 * @param mouseClick Location of the mouse click
 * @return true If the player delete button was clicked
 * @return false If the player delete button was not clicked
 */
bool Encounter::playerDeleteClicked(const sf::Vector2f &mouseClick)
{
    return playerDelete.isClicked(mouseClick);
}

/**
 * @brief Checks to see if the button handling adding an enemy was clicked
 * 
 * @param mouseClick Location of the mouse click
 * @return true If the enemy add button was clicked
 * @return false If the enemy add button was not clicked
 */
bool Encounter::enemyAddClicked(const sf::Vector2f &mouseClick)
{
    return enemyAdd.isClicked(mouseClick);
}

/**
 * @brief Checks to see if the button handling deleting an enemy was clicked
 * 
 * @param mouseClick Location of the mouse click
 * @return true If the enemy delete button was clicked
 * @return false If the enemy delete button was not clicked
 */
bool Encounter::enemyDeleteClicked(const sf::Vector2f &mouseClick)
{
    return enemyDelete.isClicked(mouseClick);
}

/**
 * @brief Starts the initiative order. Adds to the init. list from player list and enemy list.
 *        Starts the turn indicator at the right spot.
 * 
 */
void Encounter::startInitiative()
{
    playerList.sort();
    enemyList.sort();
    // start initiative
    initiativeList->clear();
    initiativeList->append(playerList);
    initiativeList->append(enemyList);

    initiativeList->setTurnIndicatorPosition();
}

/**
 * @brief Advances the turn on the init. list
 * 
 */
void Encounter::advanceInitiative()
{
    initiativeList->advanceTurn();
}

/**
 * @brief Resets the lists and ends the init. order.
 * 
 */
void Encounter::endInitiative()
{
    initiativeList->clear();
    initiativeList->resetStart();
    initiativeList->setTurnIndicatorPosition();
}

/**
 * @brief Calculates how difficult an encounter is based on the players and enemies
 * 
 */
void Encounter::calculateEncounterDifficulty()
{
    calculatePlayerXpThreshhold();
    calculateEnemyXpThreshhold();

    setDifficulty();
}

/**
 * @brief Calculates the player xp threshholds for easy, medium, hard, and deadly based off of how many players there are
 * 
 */
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

/**
 * @brief Calculates the enemy xp threshhold based off the difficulty of monsters and how many players there are
 * 
 */
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

/**
 * @brief Sets the encounter difficulty string based off of player xp threshhold and enemy xp threshhold
 * 
 */
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

/**
 * @brief Draws the encounter lists to the screen
 * 
 * @param window RenderWindow to draw the lists and buttons to.
 */
void Encounter::drawEncounter(sf::RenderWindow &window)
{
    playerList.drawList(window);
    enemyList.drawList(window);
    window.draw(playerAdd);
    window.draw(playerDelete);
    window.draw(enemyAdd);
    window.draw(enemyDelete);
}

/**
 * @brief Draws the initiative list to the screen
 * 
 * @param window RenderWindow to draw the list and buttons to.
 */
void Encounter::drawInitiative(sf::RenderWindow &window)
{
    initiativeList->drawInitiativeList(window);
    window.draw(playerAdd);
    window.draw(playerDelete);
}