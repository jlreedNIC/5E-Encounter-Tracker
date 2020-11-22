#include "creature.h"

Creature::Creature(std::string name, int maxHealth, int health, int tempHealth, int initiative, int armorClass, std::string status, int level)
{
    this->name = name;
    this->maxHealth = maxHealth;
    this->health = health;
    this->tempHealth = tempHealth;
    this->initiative = initiative;
    this->armorClass = armorClass;
    this->status = status;
    this->level = level;

    updateTextBoxes();

    nameText.setTextBoxSize(sf::Vector2f(100, 35));
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
}

void Creature::setFont(const sf::Font &font)
{
    nameText.setFont(font);
    healthText.setFont(font);
    tempHealthText.setFont(font);
    initiativeText.setFont(font);
    armorClassText.setFont(font);
    statusText.setFont(font);
}

TextBox& Creature::getTextBox(const float &x, const float &y)
{
    if(nameText.isClicked(x, y))
        return nameText;
    else if(healthText.isClicked(x, y))
        return healthText;
    else if(tempHealthText.isClicked(x, y))
        return tempHealthText;
    else if(initiativeText.isClicked(x, y))
        return initiativeText;
    else if(armorClassText.isClicked(x, y))
        return armorClassText;
    else if(statusText.isClicked(x, y))
        return statusText;
}

void Creature::edit(const float &x, const float &y, const std::string &tempValue)
{
    if(nameText.isClicked(x, y))
        nameText.setString(tempValue);
    else if(healthText.isClicked(x, y))
        healthText.setString(tempValue);
    else if(tempHealthText.isClicked(x, y))
        tempHealthText.setString(tempValue);
    else if(initiativeText.isClicked(x, y))
        initiativeText.setString(tempValue);
    else if(armorClassText.isClicked(x, y))
        armorClassText.setString(tempValue);
    else if(statusText.isClicked(x, y))
        statusText.setString(tempValue);
}

bool Creature::isClicked(const float &x, const float &y)
{
    return (nameText.isClicked(x, y) || healthText.isClicked(x, y) ||
            tempHealthText.isClicked(x, y) || initiativeText.isClicked(x, y) ||
            armorClassText.isClicked(x, y) || statusText.isClicked(x, y));
}

void Creature::draw(sf::RenderWindow &window)
{
    window.draw(nameText);
    // window.draw(nameText.getText());

    window.draw(healthText);
    // window.draw(healthText.getText());

    window.draw(tempHealthText);
    // window.draw(tempHealthText.getText());

    window.draw(initiativeText);
    // window.draw(initiativeText.getText());

    window.draw(armorClassText);
    // window.draw(armorClassText.getText());

    window.draw(statusText);
    // window.draw(statusText.getText());
}