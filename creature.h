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

        int level;
        TextBox levelText;

        Creature(std::string name="BOB", int maxHealth=0, 
                 int health=0, int tempHealth=0, int initiative=0, 
                 int armorClass=0, std::string status="NA", int level=1);

        void updateTextBoxes();
        void updateValues();

        // setters
        void setPosition(sf::Vector2f pos);
        void setPosition(float x, float y);
        void setTexture(const sf::Texture &texture);
        void setFont(const sf::Font &font);

        void clearTexture();

        TextBox& getTextBox(const float &x, const float &y);
        std::string getString(const sf::Vector2f &mouseClick);
        int getLevel();
        
        void edit(const float &x, const float &y, const std::string &tempValue);
        void edit(const sf::Vector2f &mouseClick, const std::string &tempValue);

        bool isClicked(const float &x, const float &y);
        bool isClicked(const sf::Vector2f &mouseClick);

        void draw(sf::RenderWindow &window);
        void drawInit(sf::RenderWindow &window);
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