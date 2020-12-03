#include "creature.h"

Creature::Creature(std::string name, int maxHealth, int health, int tempHealth, int initiative, int armorClass, std::string status, int level)
{
    // ostringstream ostr;

    // nameText.setString(name);
    
    // ostr << health << "/" << maxHealth;
    // healthText.setString(ostr.str());
    // ostr.str("");

    // ostr << tempHealth;
    // tempHealthText.setString(ostr.str());
    // ostr.str("");

    // ostr << initiative;
    // initiativeText.setString(ostr.str());
    // ostr.str("");

    // ostr << armorClass;
    // armorClassText.setString(ostr.str());
    // ostr.str("");

    // statusText.setString(status);

    // ostr << level;
    // levelText.setString(ostr.str());

    this->name = name;
    this->maxHealth = maxHealth;
    this->health = health;
    this->tempHealth = tempHealth;
    this->initiative = initiative;
    this->armorClass = armorClass;
    this->status = status;
    this->level = level;

    updateTextBoxes();

    nameText.setTextBoxSize(sf::Vector2f(90, 35));
    healthText.setTextBoxSize(sf::Vector2f(70, 35));
    tempHealthText.setTextBoxSize(sf::Vector2f(35, 35));
    initiativeText.setTextBoxSize(sf::Vector2f(35, 35));
    armorClassText.setTextBoxSize(sf::Vector2f(35, 35));
    statusText.setTextBoxSize(sf::Vector2f(150, 35));
    levelText.setTextBoxSize(sf::Vector2f(60, 35));
}

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

void Creature::updateValues()
{
    std::string temp;

    name = nameText.getString();
    status = statusText.getString();
    temp = levelText.getString();
    if(temp != " " && temp != "")
    {
        // level = stoi(temp);
    }

    temp = initiativeText.getString();
    if(temp.size() != 0)
    {
        initiative = stoi(temp);
    }

    temp = tempHealthText.getString();
    if(temp.size() != 0)
    {
        tempHealth = stoi(temp);
    }

    temp = armorClassText.getString();
    if(temp.size() != 0)
    {
        armorClass = stoi(temp);
    }

    temp = healthText.getString();
    if(temp != "")
    {
        health = stoi(temp);
        maxHealth = stoi(temp);
    }
}

void Creature::setPosition(sf::Vector2f pos)
{
    nameText.setTextBoxPosition(pos);
    initiativeText.setTextBoxPosition(pos.x + 100, pos.y);

    // initiativeText.setTextBoxPosition(pos);
    // nameText.setTextBoxPosition(pos.x + 100, pos.y);
    armorClassText.setTextBoxPosition(pos.x + 200, pos.y);
    healthText.setTextBoxPosition(pos.x + 250, pos.y);
    tempHealthText.setTextBoxPosition(pos.x + 325, pos.y);
    statusText.setTextBoxPosition(pos.x + 425, pos.y);
    levelText.setTextBoxPosition(pos.x + 625, pos.y);
}

void Creature::setPosition(float x, float y)
{
    sf::Vector2f pos(x, y);
    setPosition(pos);
}

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

// change return type to string
// TextBox& Creature::getTextBox(const float &x, const float &y)
// {
//     if(nameText.isClicked(x, y))
//         return nameText;
//     else if(healthText.isClicked(x, y))
//         return healthText;
//     else if(tempHealthText.isClicked(x, y))
//         return tempHealthText;
//     else if(initiativeText.isClicked(x, y))
//         return initiativeText;
//     else if(armorClassText.isClicked(x, y))
//         return armorClassText;
//     else if(statusText.isClicked(x, y))
//         return statusText;
//     else if(levelText.isClicked(x, y))
//         return levelText;
// }

std::string Creature::getString(const sf::Vector2f &mouseClick)
{
    std::string value;

    if(nameText.isClicked(mouseClick))
        value = nameText.getString();
    else if(healthText.isClicked(mouseClick))
        value = healthText.getString();
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

int Creature::getLevel()
{
    std::string tempLevel = levelText.getString();
    if(tempLevel == "")
    {
        return 0;
    }
    else return stoi(tempLevel);
}

void Creature::edit(const float &x, const float &y, const std::string &tempValue)
{
    edit(sf::Vector2f(x, y), tempValue);
    // if(nameText.isClicked(x, y))
    //     nameText.setString(tempValue);
    // else if(healthText.isClicked(x, y))
    //     healthText.setString(tempValue);
    // else if(tempHealthText.isClicked(x, y))
    //     tempHealthText.setString(tempValue);
    // else if(initiativeText.isClicked(x, y))
    //     initiativeText.setString(tempValue);
    // else if(armorClassText.isClicked(x, y))
    //     armorClassText.setString(tempValue);
    // else if(statusText.isClicked(x, y))
    //     statusText.setString(tempValue);
    // else if(levelText.isClicked(x, y))
    //     levelText.setString(tempValue);
}

void Creature::edit(const sf::Vector2f &mouseClick, const std::string &tempValue)
{
    std::istringstream istr;
    char delim;

    if(nameText.isClicked(mouseClick))
        name = tempValue;
    else if(healthText.isClicked(mouseClick))
    {
        istr.str(tempValue);
        istr >> health >> delim >> maxHealth;
    }
    else if(tempHealthText.isClicked(mouseClick))
    {
        istr.str(tempValue);
        istr >> tempHealth;
    }
    else if(initiativeText.isClicked(mouseClick))
    {
        istr.str(tempValue);
        istr >> initiative;
    }
    else if(armorClassText.isClicked(mouseClick))
    {
        istr.str(tempValue);
        istr >> armorClass;
    }
    else if(statusText.isClicked(mouseClick))
        status = tempValue;
    else if(levelText.isClicked(mouseClick))
    {
        istr.str(tempValue);
        istr >> level;
    }

    updateTextBoxes();
}

bool Creature::isClicked(const float &x, const float &y)
{
    return isClicked(sf::Vector2f(x, y));
}

bool Creature::isClicked(const sf::Vector2f &mouseClick)
{
    return (nameText.isClicked(mouseClick) || healthText.isClicked(mouseClick) ||
            tempHealthText.isClicked(mouseClick) || initiativeText.isClicked(mouseClick) ||
            armorClassText.isClicked(mouseClick) || statusText.isClicked(mouseClick) ||
            levelText.isClicked(mouseClick));
}

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