#ifndef INITIATIVELIST_H
#define INITIATIVELIST_H

#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
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
        Initiative();   //default constructor
        Initiative(const Initiative &copy);     // copy constructor
        ~Initiative();

        //list functions
        void addNodeInOrder(Creature character);    // add a creature to the initiative order
        void deleteNode(string name);               // delete a creature from the initiative order
        void append(const Initiative &copy);        // copies the contents of one list into the main list

        //getters
        int getRound() const;                       // return the initiative round
        TextBox& getTextBox(const float &x, const float &y);
        int getSize() const;
        int* getLevel();

        // edit list by name search
        void editHealth(string name, int newHealth);
        void editName(string name, string newName);
        void editMaxHealth(string name, int newMaxHealth);
        void editInit(string name, int newInit);
        void editAC(string name, int newAC);
        void editStatus(string name, string newStatus);
        void editTempHealth(string name, int newTempHealth);

        void editNode(const float &x, const float &y, const std::string &tempValue);

        //setters
        void setListTexture(const sf::Texture &texture);    // set a texture for the entire list
        void setListFont(const sf::Font &font);             // set a font for the entire list
        void setPosition(sf::Vector2f pos);
        void setPosition(float x, float y);
        void setRoundText();

        // bool functions
        bool isNodeClicked(const float &x, const float &y);

        // output list
        string listToString() const;
        string nodeToString(string name) const;

        void drawList(sf::RenderWindow &window, sf::Vector2f pos);  // remove?
        void drawList(sf::RenderWindow &window);

        string advanceTurn();
        void resetStart();

    private:
        Node* mHead;
        Node* mStart; //keeps track of where you are in initiative
        int round;    //keeps track of initiative rounds
        int size;     //keeps track of size of list

        string nodeToString(Node *ptr) const;

        void drawNode(sf::RenderWindow &window, sf::Vector2f pos, Node* &ptr); // remove?
        void drawNode(sf::RenderWindow &window, Node* &ptr);

        sf::Text headers[6];
        sf::Text roundText;
};

#endif