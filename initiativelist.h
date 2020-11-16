#ifndef INITIATIVELIST_H
#define INITIATIVELIST_H

#include "diceroll.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "creature.h"

using std::string;
using std::ostringstream;
using std::setw;

//turn struct into class
//can use a creature class for parent class
// child classes can be npc, player, monster, etc
// struct Creature
// {
//     string name;
//     int maxHealth;
//     int health;
//     int tempHealth;
//     int initiative;
//     int armorClass;
//     string status;

//     Creature() {};
//     Creature(string name, int maxHealth, int health, int tempHealth, int initiative, int armorClass, string status)
//     {
//         this->name = name;
//         this->maxHealth = maxHealth;
//         this->health = health;
//         this->tempHealth = tempHealth;
//         this->initiative = initiative;
//         this->armorClass = armorClass;
//         this->status = status;
//     }
// };

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
        Initiative();
        ~Initiative();

        //list functions
        void addNodeInOrder(Creature character);    //add a creature to the initiative order
        void deleteNode(string name);               //delete a creature from the initiative order

        //getters
        int getRound() const;                       //return the initiative round

        //edit list
        void editHealth(string name, int newHealth);
        void editName(string name, string newName);
        void editMaxHealth(string name, int newMaxHealth);
        void editInit(string name, int newInit);
        void editAC(string name, int newAC);
        void editStatus(string name, string newStatus);
        void editTempHealth(string name, int newTempHealth);

        //output list
        string listToString() const;
        string nodeToString(string name) const;

        void drawList(sf::RenderWindow &window, sf::Vector2f pos);

        string advanceTurn();
        void resetStart();

    private:
        Node* mHead;
        Node* mStart; //keeps track of where you are in initiative
        int round;  //keeps track of initiative rounds

        string nodeToString(Node *ptr) const;
        void drawNode(sf::RenderWindow &window, sf::Vector2f pos, Node* &ptr);
};

#endif