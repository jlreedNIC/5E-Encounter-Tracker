#ifndef CREATURE_H
#define CREATURE_H

#include "textbox.h"
#include <string>
#include <sstream>
#include <iostream>

// using std::string;
// using std::ostringstream;

class Creature //: sf::Drawable
{
    public:
        std::string name;
        TextBox nameText;

        int maxHealth;
        int health;
        TextBox healthText;

        int tempHealth;
        TextBox tempHealthText;

        int initiative;
        TextBox initiativeText;

        int armorClass;
        TextBox armorClassText;
        
        std::string status;
        TextBox statusText;

        Creature(std::string name="BOB", int maxHealth=0, 
                 int health=0, int tempHealth=0, int initiative=0, 
                 int armorClass=0, std::string status="NA");

        void updateTextBoxes();

        void setPosition(sf::Vector2f &pos);

        // void draw(sf::RenderTarget& target, sf::RenderStates state) const
        // {
        //     target.draw(nameText);
        //     // target.draw(nameText.getText());

        //     target.draw(healthText);
        //     // target.draw(healthText.getText());

        //     target.draw(tempHealthText);
        //     // target.draw(tempHealthText.getText());

        //     target.draw(initiativeText);
        //     // target.draw(initiativeText.getText());

        //     target.draw(armorClassText);
        //     // target.draw(armorClassText.getText());

        //     target.draw(statusText);
        //     // target.draw(statusText.getText());
        // }
    private:
};

#endif