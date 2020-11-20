#include "initiativelist.h"

/**
 * @brief Construct a new circularly linked list
 * 
 */
Initiative::Initiative()
{
    mHead = nullptr;
    mStart = mHead;
    round = 0;
}

/**
 * @brief Constructs a new circularly linked list based off of another list
 * 
 * @param copy List to be copied
 */
Initiative::Initiative(const Initiative &copy)
{
    Node* copyPtr = copy.mHead;

    if(copy.mHead == nullptr)
    {
        mHead = nullptr;
        mStart = mHead;
        round = 0;
    }
    else
    {
        mHead = nullptr;
        mStart = mHead;
        round = 0;

        do
        {
            addNodeInOrder(copyPtr->character);
            copyPtr = copyPtr->next;
        }while(copyPtr != copy.mHead);
    }
}

/**
 * @brief Destroy the list
 * 
 */
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

/**
 * @brief Adds a new node to the list, sorted by initiative
 * 
 * @param character 
 */
void Initiative::addNodeInOrder(Creature character)
{
    Node* ptr = mHead;
    bool found = false;

    if(ptr == nullptr)
    {
        Node* nodePtr = new Node(character);
        mHead = mStart = nodePtr;
        mHead->next = mHead->prev = mHead;
        nodePtr->character.updateTextBoxes();
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
        nodePtr->character.updateTextBoxes();
    }
    
}

/**
 * @brief Deletes a specific node
 * 
 * @param name Parameter to search for the node to delete
 */
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

/**
 * @brief Copies the contents of a list to this list
 * 
 * @param copy List to be copied
 */
void Initiative::append(const Initiative &copy)
{
    Node* ptr = copy.mHead;
    if(ptr != nullptr)
    {
        do
        {
            addNodeInOrder(ptr->character);
            ptr = ptr->next;
        }while(ptr != copy.mHead);
    }
}

/**
 * @brief Returns the round counter
 * 
 * @return int 
 */
int Initiative::getRound() const
{
    return round;
}

/**
 * @brief Updates the health value
 * 
 * @param name Parameter to search the list by
 * @param newHealth New value
 */
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
        ptr->character.updateTextBoxes();
    }
}

/**
 * @brief Updates the name value
 * 
 * @param name Parameter to seach the list by
 * @param newName New value
 */
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
        ptr->character.updateTextBoxes();
    }
}

/**
 * @brief Updates the max health value
 * 
 * @param name Parameter to seach the list by
 * @param newName New value
 */
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
        ptr->character.updateTextBoxes();
    }
}

/**
 * @brief Updates the initiative value
 * 
 * @param name Parameter to seach the list by
 * @param newName New value
 */
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
        ptr->character.updateTextBoxes();
    }
}

/**
 * @brief Updates the armor class value
 * 
 * @param name Parameter to seach the list by
 * @param newName New value
 */
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
        ptr->character.updateTextBoxes();
    }
}

/**
 * @brief Updates the status value
 * 
 * @param name Parameter to seach the list by
 * @param newName New value
 */
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
        ptr->character.updateTextBoxes();
    }
}

/**
 * @brief Updates the temp health value
 * 
 * @param name Parameter to seach the list by
 * @param newName New value
 */
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
        ptr->character.updateTextBoxes();
    }
}

/**
 * @brief Sets the same texture for all the textbox objects in the list
 * 
 * @param texture Texture to be used
 */
void Initiative::setListTexture(const sf::Texture &texture)
{
    Node* ptr = mHead;

    if(mHead != nullptr)
    {
        do
        {
            ptr->character.setTexture(texture);
            ptr = ptr->next;
        }while(ptr != mHead);
    }
}

/**
 * @brief Sets the same font for all the textbox objects in the list
 * 
 * @param font Font to be used
 */
void Initiative::setListFont(const sf::Font &font)
{
    Node* ptr = mHead;

    if(mHead != nullptr)
    {
        do
        {
            ptr->character.setFont(font);
            ptr = ptr->next;
        }while(ptr != mHead);
    }
}

/**
 * @brief Advances the list in the turn order. Currently set up to return a string
 * 
 * @return string 
 */
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

/**
 * @brief Resets the start position to the beginning of the list
 * 
 */
void Initiative::resetStart()
{
    mStart = mHead;
    round = 0;
}

/**
 * @brief Converts the contents of the list to a string
 * 
 * @return string 
 */
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

/**
 * @brief Converts the contents of a specific node to a string
 * 
 * @param name Parameter to search for
 * @return string 
 */
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

/**
 * @brief Converts the contents of a specific node to a string
 * 
 * @param ptr Parameter to search for
 * @return string 
 */
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

/**
 * @brief Draws entire list to a window object by setting position of the nodes
 * 
 * @param window Window to be drawn to
 * @param pos position of nodes to be drawn
 */
void Initiative::drawList(sf::RenderWindow &window, sf::Vector2f pos)
{
    Node *ptr = mHead;

    do
    {
        drawNode(window, pos, ptr);
        ptr = ptr->next;
        pos.y += 40;
    }while(ptr != mHead);
}

/**
 * @brief Draws a specific node to a window object given a specific position
 * 
 * @param window 
 * @param pos 
 * @param ptr 
 */
void Initiative::drawNode(sf::RenderWindow &window, sf::Vector2f pos, Node* &ptr)
{
    if(ptr != nullptr)
    {
        sf::Font font;
        font.loadFromFile("Fonts/Roboto-Thin.ttf");

        ptr->character.setPosition(pos);

        ptr->character.nameText.getText().setFont(font);
        ptr->character.armorClassText.getText().setFont(font);
        ptr->character.healthText.getText().setFont(font);
        ptr->character.initiativeText.getText().setFont(font);
        ptr->character.statusText.getText().setFont(font);
        ptr->character.tempHealthText.getText().setFont(font);
        
        window.draw(ptr->character.nameText);
        window.draw(ptr->character.nameText.getText());

        window.draw(ptr->character.armorClassText);
        window.draw(ptr->character.armorClassText.getText());

        window.draw(ptr->character.healthText);
        window.draw(ptr->character.healthText.getText());

        window.draw(ptr->character.initiativeText);
        window.draw(ptr->character.initiativeText.getText());

        window.draw(ptr->character.statusText);
        window.draw(ptr->character.statusText.getText());

        window.draw(ptr->character.tempHealthText);
        window.draw(ptr->character.tempHealthText.getText());
    }
}

/**
 * @brief Draws the entire list to the window object
 * 
 * @param window Window to be drawn to
 */
void Initiative::drawList(sf::RenderWindow &window)
{
    Node *ptr = mHead;

    if(ptr != nullptr)
    {
        do
        {
            drawNode(window, ptr);
            ptr = ptr->next;
        }while(ptr != mHead);
    }
}

/**
 * @brief Draws a specific node to the window object
 * 
 * @param window Window to be drawn to
 * @param ptr Node to be drawn
 */
void Initiative::drawNode(sf::RenderWindow &window, Node* &ptr)
{
    if(ptr != nullptr)
    {
        ptr->character.draw(window);
    }
}