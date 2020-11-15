#include "creature.h"

Creature::Creature(std::string name, int maxHealth, int health, int tempHealth, int initiative, int armorClass, std::string status)
{
    this->name = name;
    this->maxHealth = maxHealth;
    this->health = health;
    this->tempHealth = tempHealth;
    this->initiative = initiative;
    this->armorClass = armorClass;
    this->status = status;

    updateTextBoxes();

    nameText.setTextBoxSize(sf::Vector2f(140, 35));
    maxHealthText.setTextBoxSize(sf::Vector2f(50, 35));
    healthText.setTextBoxSize(sf::Vector2f(50, 35));
    tempHealthText.setTextBoxSize(sf::Vector2f(50, 35));
    initiativeText.setTextBoxSize(sf::Vector2f(50, 35));
    armorClassText.setTextBoxSize(sf::Vector2f(50, 35));
    statusText.setTextBoxSize(sf::Vector2f(50, 35));
}

void Creature::updateTextBoxes()
{
    std::ostringstream ostr;

    nameText.setString(name);

    ostr << "/" << maxHealth;
    maxHealthText.setString(ostr.str());
    ostr.str("");

    ostr << health;
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
}

void Creature::setPosition(sf::Vector2f &pos)
{
    initiativeText.setTextBoxPosition(pos);
    nameText.setTextBoxPosition(pos.x + 100, pos.y);
    armorClassText.setTextBoxPosition(pos.x + 250, pos.y);
    healthText.setTextBoxPosition(pos.x + 325, pos.y);
    maxHealthText.setTextBoxPosition(pos.x + 350, pos.y);
    tempHealthText.setTextBoxPosition(pos.x + 425, pos.y);
    statusText.setTextBoxPosition(pos.x + 575, pos.y);
}