#include "initiativelist.h"

Initiative::Initiative()
{
    mHead = nullptr;
    mStart = mHead;
    round = 0;
}

Initiative::~Initiative()
{
    if(mHead != nullptr)
    {
        Node *ptr = mHead;
        
        while(ptr != nullptr)
        {
            mHead = mHead->next;
            if(ptr->prev != nullptr) 
            {
                if(mHead == mHead->next) mHead = nullptr;
                ptr->prev->next = nullptr;
                ptr->prev = nullptr;
            }
            if(ptr->next != nullptr)
            {
                ptr->next->prev = nullptr;
                ptr->next = nullptr;
            }
            
            delete ptr;
            ptr = mHead;
        }
        mHead = ptr = mStart = nullptr;
    }
}

void Initiative::addNodeInOrder(Creature character)
{
    Node* ptr = mHead;
    bool found = false;

    if(ptr == nullptr)
    {
        Node* nodePtr = new Node(character);
        mHead = mStart = nodePtr;
        mHead->next = mHead->prev = mHead;
    }
    else
    {
        do
        {
            if(character.initiative >= ptr->character.initiative) found = true;
            else ptr = ptr->next;
        }while(ptr != mHead && !found);

        Node* nodePtr = new Node(character, ptr->prev, ptr);
        ptr->prev->next = nodePtr;
        ptr->prev = nodePtr;
        if(ptr == mHead && mHead->prev->character.initiative >= mHead->character.initiative) mHead = mStart = ptr->prev;
    }
}

void Initiative::deleteNode(string name)
{
    Node *ptr = mHead;
    bool found = false;

    if(ptr == nullptr) return;
    do
    {
        if(ptr->character.name == name) found = true;
        else ptr = ptr->next;
        
    }while(ptr != mHead && !found);

    if(found)
    {
        if(ptr == mHead) mHead = mStart = mHead->next;
        ptr->next->prev = ptr->prev;
        ptr->prev->next = ptr->next;
        ptr->next = nullptr;
        ptr->prev = nullptr;
        if(ptr == mHead) mHead = mStart = nullptr;
        delete ptr;
        ptr = nullptr;
    }
}

int Initiative::getRound() const
{
    return round;
}

void Initiative::editHealth(string name, int newHealth)
{
    Node* ptr = mHead;
    if(ptr == nullptr) return;

    bool found = false;

    do
    {
        if(ptr->character.name == name) found = true;
        else ptr = ptr->next;
    }while(ptr != mHead && !found);

    if(found)
    {
        ptr->character.health = newHealth;
    }
}

void Initiative::editName(string name, string newName)
{
    Node* ptr = mHead;
    if(ptr == nullptr) return;

    bool found = false;

    do
    {
        if(ptr->character.name == name) found = true;
        else ptr = ptr->next;
    }while(ptr != mHead && !found);
    
    if(found)
    {
        ptr->character.name = newName;
    }
}

void Initiative::editMaxHealth(string name, int newMaxHealth)
{
    Node* ptr = mHead;
    if(ptr == nullptr) return;

    bool found = false;

    do
    {
        if(ptr->character.name == name) found = true;
        else ptr = ptr->next;
    }while(ptr != mHead && !found);
    
    if(found)
    {
        ptr->character.maxHealth = newMaxHealth;
    }
}

void Initiative::editInit(string name, int newInit)
{
    Node* ptr = mHead;
    if(ptr == nullptr) return;

    bool found = false;

    do
    {
        if(ptr->character.name == name) found = true;
        else ptr = ptr->next;
    }while(ptr != mHead && !found);
    
    if(found)
    {
        ptr->character.initiative = newInit;
    }
}

void Initiative::editAC(string name, int newAC)
{
    Node* ptr = mHead;
    if(ptr == nullptr) return;

    bool found = false;

    do
    {
        if(ptr->character.name == name) found = true;
        else ptr = ptr->next;
    }while(ptr != mHead && !found);
    
    if(found)
    {
        ptr->character.armorClass = newAC;
    }
}

void Initiative::editStatus(string name, string newStatus)
{
    Node* ptr = mHead;
    if(ptr == nullptr) return;

    bool found = false;

    do
    {
        if(ptr->character.name == name) found = true;
        else ptr = ptr->next;
    }while(ptr != mHead && !found);
    
    if(found)
    {
        ptr->character.status = newStatus;
    }
}

void Initiative::editTempHealth(string name, int newTempHealth)
{
    Node* ptr = mHead;
    if(ptr == nullptr) return;

    bool found = false;

    do
    {
        if(ptr->character.name == name) found = true;
        else ptr = ptr->next;
    }while(ptr != mHead && !found);
    
    if(found)
    {
        ptr->character.tempHealth = newTempHealth;
    }
}

string Initiative::advanceTurn()
{
    if(mHead == nullptr) return "";
    else
    {
        ostringstream ostr;
        
        Node* ptr = mStart;
        do
        {
            ostr << nodeToString(ptr);
            ptr = ptr->next;
        }while(ptr != mStart);

        if(mStart == mHead) round++;
        mStart = mStart->next;
        
        return ostr.str();
    }
}

void Initiative::resetStart()
{
    mStart = mHead;
    round = 0;
}

string Initiative::listToString() const
{
    
    ostringstream ostr;
    Node *ptr = mHead;
    
    if(ptr == nullptr) return ostr.str();

    do
    {
        
        ostr << nodeToString(ptr);
        ptr = ptr->next;
    }while(ptr != mHead);

    return ostr.str();
}

string Initiative::nodeToString(string name) const
{
    Node* ptr = mHead;
    if(ptr == nullptr) return "";

    bool found = false;
    do 
    {
        if(ptr->character.name == name) found = true;
        else ptr = ptr->next;
    }while(ptr != mHead && !found);

    if(found) return nodeToString(ptr);
    else return "";
}

string Initiative::nodeToString(Node *ptr) const
{
    ostringstream ostr;

    if(ptr != nullptr)
    {
        ostr << setw(11) << ptr->character.initiative << setw(11) << ptr->character.name;
        ostr << setw(5) << ptr->character.health << "/" << ptr->character.maxHealth;
        ostr << setw(8) << ptr->character.tempHealth;
        ostr << setw(4) << ptr->character.armorClass << setw(20) << ptr->character.status << "\n";
    }

    return ostr.str();
}