/**
 * @file creature.h
 * @author Jordan Reed
 * @brief Program to track encounters for D&D 5E
 * @date 2020-12-10
 * 
 */

#ifndef CREATURE_H
#define CREATURE_H

#include "textbox.h"
#include <string>
#include <sstream>
#include <iostream>

// using std::string;
// using std::ostringstream;

class Creature
{
    public:
        // base values of the creature

        std::string name;
        TextBox nameText;

        int maxHealth;
        int health;
        TextBox healthText;

        int tempHealth;
        TextBox tempHealthText;

        // change to float
        int initiative;
        TextBox initiativeText;

        int armorClass;
        TextBox armorClassText;
        
        std::string status;
        TextBox statusText;

        int level;
        TextBox levelText;

        // constructor
        Creature(std::string name="BOB", int maxHealth=0, 
                 int health=0, int tempHealth=0, int initiative=0, 
                 int armorClass=0, std::string status="NA", int level=1);

        void updateTextBoxes();     // update the string value of the textboxes to the corresponding variable
        void updateValues();        // update the different variables from the corresponding textbox

        // setters
        void setPosition(sf::Vector2f pos);             // sets the position of the creature textboxes
        void setPosition(float x, float y);             // sets the position of the creature textboxes
        void setTexture(const sf::Texture &texture);    // sets the texture for the textboxes
        void setFont(const sf::Font &font);             // sets the font for the textboxes

        void clearTexture();                            // clears the texture from the textboxes

        // getters
        std::string getString(const sf::Vector2f &mouseClick);  // gets the string value of the text box at a certain position
        int getLevel();                                         // gets the level of the creature
        
        void edit(const float &x, const float &y, const std::string &tempValue); // edits the string value at a certain position
        void edit(const sf::Vector2f &mouseClick, const std::string &tempValue); // edits the string value at a certain position

        bool isClicked(const float &x, const float &y);     // checks to see if any text box in the creature object was clicked
        bool isClicked(const sf::Vector2f &mouseClick);     // checks to see if any text box in the creature object was clicked

        void draw(sf::RenderWindow &window);        // draws the creature object to the render window
        void drawInit(sf::RenderWindow &window);    // draws only the textboxes needed for the initiative screen
    private:
};

#endif