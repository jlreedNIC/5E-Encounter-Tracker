/**
 * @file initiativelist.h
 * @author Jordan Reed
 * @brief Program to track encounters for D&D 5E
 * @date 2020-12-10
 * 
 */

#ifndef INITIATIVELIST_H
#define INITIATIVELIST_H

#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "creature.h"
#include "diceroll.h"

using std::string;
using std::ostringstream;
using std::setw;

struct Node
{
    Creature character;
    Node* next;
    Node* prev;

    Node() {};
    Node(Creature character, Node* prev=nullptr, Node* next=nullptr)
    {
        this->character = character;
        this->prev = prev;
        this->next = next;
    }
};

class Initiative
{
    public:
        Initiative();                           //default constructor
        Initiative(const Initiative &copy);     // copy constructor
        ~Initiative();

        void save(std::fstream &file);          // saves the list to the file as part of a larger save function
        void load(std::fstream &file);          // loads a list from a file as part of a larger load function

        //list functions
        void addNodeInOrder(Creature character);    // add a creature to the initiative order
        void deleteNode(string name);               // delete a creature from the initiative order searching by name
        void deleteNode(const sf::Vector2f &mouseClick);    // deletes a node from the list using position to find the right node
        void deleteLast();                                  // deletes the node before the head pointer
        void append(const Initiative &copy);        // copies the contents of one list into the main list
        void clear();                               // clears all nodes from the list
        void sort();                                // sorts the list by initiative order

        //getters
        int getRound() const;                               // return the initiative round
        int getSize() const;                                // returns the size of the list
        std::string getLevel();                             // returns the levels of all creatures in the list
        std::string getString(sf::Vector2f &mouseClick);    // returns the string at a certain point in the list
        sf::Vector2f getPosition() const;                   // gets the beginning position of the list
        std::string getFirstName();                         // gets the name of the first creature in the list

        // edit list by name search
        void editHealth(string name, int newHealth);
        void editName(string name, string newName);
        void editMaxHealth(string name, int newMaxHealth);
        void editInit(string name, int newInit);
        void editAC(string name, int newAC);
        void editStatus(string name, string newStatus);
        void editTempHealth(string name, int newTempHealth);

        // edits a string at a certain position
        void edit(const float &x, const float &y, const std::string &tempValue);
        void edit(const sf::Vector2f &mouseClick, const std::string &tempValue);

        //setters
        void setListTexture(const sf::Texture &texture);    // set a texture for the entire list
        void setListFont(const sf::Font &font);             // set a font for the entire list
        void setPosition(sf::Vector2f pos);                 // sets the position of all nodes in the list
        void setPosition(float x, float y);                 // sets the position of all nodes in the list
        void setRoundText();                                // sets the text for the round

        void clearTexture();                                // clears the texture from the list

        // bool functions
        // FIX: change to isClicked
        bool isNodeClicked(const float &x, const float &y); // checks to see if a node was clicked
        bool isNodeClicked(const sf::Vector2f &mouseClick); // checks to see if a node was clicked

        // output list
        string listToString() const;            // returns a string containing the entire list
        string nodeToString(string name) const; // returns a string containing one node

        void drawList(sf::RenderWindow &window, sf::Vector2f pos);  // remove?
        void drawList(sf::RenderWindow &window);    // draws the entire list to the window

        void drawInitiativeList(sf::RenderWindow &window);  // draws the info needed for the initiative list

        void advanceTurn();                 // advances the mStart pointer for the intiative list
        void resetStart();                  // resets the mStart pointer
        void setTurnIndicatorPosition();    // sets the turn indicator to point to where mStart is

    private:
        Node* mHead;
        Node* mStart; //keeps track of where you are in initiative
        int round;    //keeps track of initiative rounds
        int size;     //keeps track of size of list

        string nodeToString(Node *ptr) const;   // returns a string containing all info in one node

        void drawNode(sf::RenderWindow &window, sf::Vector2f pos, Node* &ptr); // remove?
        void drawNode(sf::RenderWindow &window, Node* &ptr);        // draws one node to the window

        void drawInitNode(sf::RenderWindow &window, Node* &ptr);    // draws one node to the window for initiative

        sf::CircleShape turnIndicator;      // an indicator for whose turn it is in initiative
        sf::Text roundText;                 // text object containing what round in initiative it is
};

#endif