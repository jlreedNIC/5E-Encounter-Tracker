#ifndef CREATURE_H
#define CREATURE_H

#include "textbox.h"
#include <string>
#include <sstream>
#include <iostream>

using std::string;
using std::ostringstream;

class Creature
{
    public:
        string name;
        TextBox nameText;
        int maxHealth;
        TextBox maxHealthText;
        int health;
        TextBox healthText;
        int tempHealth;
        TextBox tempHealthText;
        int initiative;
        TextBox initiativeText;
        int armorClass;
        TextBox armorClassText;
        string status;
        TextBox statusText;

        Creature(string name="BOB", int maxHealth=0, int health=0, int tempHealth=0, int initiative=0, int armorClass=0, string status="NA");

        void updateTextBoxes();

        void setPosition(sf::Vector2f &pos);
    private:
};

#endif