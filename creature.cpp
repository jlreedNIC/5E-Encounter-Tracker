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

void Creature::setPosition(sf::Vector2f &pos)
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

void Creature::setTexture(const sf::Texture &texture)
{
    nameText.setTexture(&texture);
    healthText.setTexture(&texture);
    tempHealthText.setTexture(&texture);
    initiativeText.setTexture(&texture);
    armorClassText.setTexture(&texture);
    statusText.setTexture(&texture);
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

void Creature::draw(sf::RenderWindow &window)
{
    window.draw(nameText);
    window.draw(nameText.getText());

    window.draw(healthText);
    window.draw(healthText.getText());

    window.draw(tempHealthText);
    window.draw(tempHealthText.getText());

    window.draw(initiativeText);
    window.draw(initiativeText.getText());

    window.draw(armorClassText);
    window.draw(armorClassText.getText());

    window.draw(statusText);
    window.draw(statusText.getText());
}