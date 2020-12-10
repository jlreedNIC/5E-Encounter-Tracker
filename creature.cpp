/**
 * @file creature.cpp
 * @author Jordan Reed
 * @brief Program to track encounters for D&D 5E
 * @date 2020-12-10
 * 
 */

#include "creature.h"

/**
 * @brief Construct a new Creature object using default settings
 * 
 * @param name String that contains the creature's name
 * @param maxHealth Int that contains the creature's maximum health
 * @param health Int that contains the creature's current health
 * @param tempHealth Int that contains the creature's temporary hit points
 * @param initiative Int that contains the creature's initiative score
 * @param armorClass Int that contains the creature's armor class
 * @param status String that contains the status of the creature
 * @param level Int that contains the level/XP rating of the creature
 */
Creature::Creature(std::string name, int maxHealth, int health, int tempHealth, int initiative, int armorClass, std::string status, int level)
{
    // set underlying variables
    this->name = name;
    this->maxHealth = maxHealth;
    this->health = health;
    this->tempHealth = tempHealth;
    this->initiative = initiative;
    this->armorClass = armorClass;
    this->status = status;
    this->level = level;

    updateTextBoxes();

    // set base size for each box
    nameText.setTextBoxSize(sf::Vector2f(90, 35));
    healthText.setTextBoxSize(sf::Vector2f(70, 35));
    tempHealthText.setTextBoxSize(sf::Vector2f(35, 35));
    initiativeText.setTextBoxSize(sf::Vector2f(35, 35));
    armorClassText.setTextBoxSize(sf::Vector2f(35, 35));
    statusText.setTextBoxSize(sf::Vector2f(150, 35));
    levelText.setTextBoxSize(sf::Vector2f(60, 35));
}

/**
 * @brief Updates the textboxes with the corresponding variables. Used in calculations.
 * 
 */
void Creature::updateTextBoxes()
{
    std::ostringstream ostr;

    nameText.setString(name);

    ostr << health << "/" << maxHealth;
    healthText.setString(ostr.str());
    ostr.str("");

    ostr << tempHealth;
    tempHealthText.setString(ostr.str());
    ostr.str("");

    ostr << initiative;
    initiativeText.setString(ostr.str());
    ostr.str("");

    ostr << armorClass;
    armorClassText.setString(ostr.str());
    ostr.str("");

    statusText.setString(status);

    ostr << level;
    levelText.setString(ostr.str());
    ostr.str("");
}

/**
 * @brief Updates the base variables with the string from the corresponding textBox
 * 
 */
 // FIX: currently has and issue with istr and the getString
void Creature::updateValues()
{
    std::istringstream istr;
    std::ostringstream ostr;
    std::string temp;

    name = nameText.getString();
    status = statusText.getString();

    temp = levelText.getString();
    // temp = "76hello";
    // std::cout << temp << "\n";
    istr.str(temp);
    istr >> level;
    ostr << level;
    istr.str(ostr.str());
    istr >> level;
    ostr.str("");
    // std::cout << temp << istr.str() << " " << level << "\n";

    temp = initiativeText.getString();
    istr.str(temp);
    istr >> initiative;
    ostr << initiative;
    istr.str(ostr.str());
    istr >> initiative;
    ostr.str("");

    temp = tempHealthText.getString();
    istr.str(temp);
    istr >> tempHealth;
    ostr << tempHealth;
    istr.str(ostr.str());
    istr >> tempHealth;
    ostr.str("");

    temp = armorClassText.getString();
    istr.str(temp);
    istr >> armorClass;
    ostr << armorClass;
    istr.str(ostr.str());
    istr >> armorClass;
    ostr.str("");

    char delim;
    temp = healthText.getString();
    istr.str(temp);
    istr >> health >> delim >> maxHealth;
    ostr << health << delim << maxHealth;
    istr.str(ostr.str());
    istr >> health >> delim >> maxHealth;
    std::cout << temp << " " << istr.str() << " " << ostr.str() << " " << health << delim << maxHealth << "\n";
    ostr.str("");
}

/**
 * @brief Sets the position of each text box so the creature object is all in a row
 * 
 * @param pos Position of the first textbox
 */
void Creature::setPosition(sf::Vector2f pos)
{
    nameText.setTextBoxPosition(pos);
    initiativeText.setTextBoxPosition(pos.x + 150, pos.y);
    armorClassText.setTextBoxPosition(pos.x + 200, pos.y);
    healthText.setTextBoxPosition(pos.x + 250, pos.y);
    tempHealthText.setTextBoxPosition(pos.x + 325, pos.y);
    statusText.setTextBoxPosition(pos.x + 425, pos.y);
    levelText.setTextBoxPosition(pos.x + 625, pos.y);
}

/**
 * @brief Sets the position of each text box so the creature object is all in a row
 * 
 * @param x X coordinate of the first textbox
 * @param y Y coordinate of the first textbox
 */
void Creature::setPosition(float x, float y)
{
    sf::Vector2f pos(x, y);
    setPosition(pos);
}

/**
 * @brief Sets the texture for all the textboxes
 * 
 * @param texture Texture to be used in the textboxes
 */
void Creature::setTexture(const sf::Texture &texture)
{
    nameText.setTexture(texture);
    healthText.setTexture(texture);
    tempHealthText.setTexture(texture);
    initiativeText.setTexture(texture);
    armorClassText.setTexture(texture);
    statusText.setTexture(texture);
    levelText.setTexture(texture);
}

/**
 * @brief Sets the font for all the textboxes
 * 
 * @param font Font to be used for the textboxes
 */
void Creature::setFont(const sf::Font &font)
{
    nameText.setFont(font);
    healthText.setFont(font);
    tempHealthText.setFont(font);
    initiativeText.setFont(font);
    armorClassText.setFont(font);
    statusText.setFont(font);
    levelText.setFont(font);
}

/**
 * @brief Clears the texture from the textboxes
 * 
 */
void Creature::clearTexture()
{
    nameText.clearTexture();
    healthText.clearTexture();
    tempHealthText.clearTexture();
    initiativeText.clearTexture();
    armorClassText.clearTexture();
    statusText.clearTexture();
    levelText.clearTexture();
}

/**
 * @brief Gets the string value from a textbox located at a certain position
 * 
 * @param mouseClick Position of the desired string
 * @return std::string Copy of the string at the location
 */
std::string Creature::getString(const sf::Vector2f &mouseClick)
{
    std::string value;
    std::istringstream istr;
    std::ostringstream ostr;
    int number;

    if(nameText.isClicked(mouseClick))
        value = nameText.getString();
    else if(healthText.isClicked(mouseClick))
    {
        // gets only the health value, not the maxhealth
        value = healthText.getString();
        istr.str(value);
        istr >> number;
        ostr << number;
        value = ostr.str();
    }
    else if(tempHealthText.isClicked(mouseClick))
        value = tempHealthText.getString();
    else if(initiativeText.isClicked(mouseClick))
        value = initiativeText.getString();
    else if(armorClassText.isClicked(mouseClick))
        value = armorClassText.getString();
    else if(statusText.isClicked(mouseClick))
        value = statusText.getString();
    else if(levelText.isClicked(mouseClick))
        value = levelText.getString();
    
    return value;
}

/**
 * @brief Gets the level/XP rating of the creature
 * 
 * @return int Copy of the level/XP in int format
 */
int Creature::getLevel()
{
    std::string tempLevel = levelText.getString();
    if(tempLevel == "")
    {
        return 0;
    }
    else return stoi(tempLevel);
}

/**
 * @brief Updates the textbox string at the location given
 * 
 * @param x X coordinate of the textbox to be edited
 * @param y Y coordinate of the textbox to be edited
 * @param tempValue String to udpate the textbox with
 */
void Creature::edit(const float &x, const float &y, const std::string &tempValue)
{
    edit(sf::Vector2f(x, y), tempValue);
}

/**
 * @brief Updates the textbox string at the location given
 * 
 * @param mouseClick Position of the textbox to be edited
 * @param tempValue String to update the textbox with
 */
 // FIX: want to use the setString to be able to use the cursor
void Creature::edit(const sf::Vector2f &mouseClick, const std::string &tempValue)
{
    std::istringstream istr;
    char delim;

    if(nameText.isClicked(mouseClick))
        name = tempValue;
        // nameText.setString(tempValue);
    else if(healthText.isClicked(mouseClick))
    {
        istr.str(tempValue);
        istr >> health >> delim >> maxHealth;
    }
        // healthText.setString(tempValue);
    else if(tempHealthText.isClicked(mouseClick))
    {
        istr.str(tempValue);
        istr >> tempHealth;
    }
        // tempHealthText.setString(tempValue);
    else if(initiativeText.isClicked(mouseClick))
    {
        istr.str(tempValue);
        istr >> initiative;
    }
        // initiativeText.setString(tempValue);
    else if(armorClassText.isClicked(mouseClick))
    {
        istr.str(tempValue);
        istr >> armorClass;
    }
        // armorClassText.setString(tempValue);
    else if(statusText.isClicked(mouseClick))
        status = tempValue;
        // statusText.setString(tempValue);
    else if(levelText.isClicked(mouseClick))
    {
        istr.str(tempValue);
        istr >> level;
    }
        // levelText.setString(tempValue);
    
    updateTextBoxes();
    // updateValues();
}

/**
 * @brief Checks to see if one of the textboxes in the creature object was clicked
 * 
 * @param x X coordinate of mouse click
 * @param y Y coordinate of mouse click
 * @return true If one of the textboxes was clicked
 * @return false If none of the textboxes was clicked
 */
bool Creature::isClicked(const float &x, const float &y)
{
    return isClicked(sf::Vector2f(x, y));
}

/**
 * @brief Checks to see if one of the textboxes in the creature object was clicked
 * 
 * @param mouseClick Position of the mouse click
 * @return true If one of the textboxes was clicked
 * @return false If none of the textboxes was clicked
 */
bool Creature::isClicked(const sf::Vector2f &mouseClick)
{
    return (nameText.isClicked(mouseClick) || healthText.isClicked(mouseClick) ||
            tempHealthText.isClicked(mouseClick) || initiativeText.isClicked(mouseClick) ||
            armorClassText.isClicked(mouseClick) || statusText.isClicked(mouseClick) ||
            levelText.isClicked(mouseClick));
}

/**
 * @brief Draws all the text boxes to the window
 * 
 * @param window RenderWindow to be drawn to
 */
void Creature::draw(sf::RenderWindow &window)
{
    window.draw(nameText);
    window.draw(healthText);
    window.draw(tempHealthText);
    window.draw(initiativeText);
    window.draw(armorClassText);
    window.draw(statusText);
    window.draw(levelText);
}

/**
 * @brief Draws the textboxes needed for the initiative screen. 
 *        Name, health, tempHP, initiative, AC and status
 * 
 * @param window 
 */
void Creature::drawInit(sf::RenderWindow &window)
{
    window.draw(nameText);
    window.draw(healthText);
    window.draw(tempHealthText);
    window.draw(initiativeText);
    window.draw(armorClassText);
    window.draw(statusText);
}