/**
 * @file initiativelist.cpp
 * @author Jordan Reed
 * @brief Program to track encounters for D&D 5E
 * @date 2020-12-10
 * 
 */

#include "initiativelist.h"

/**
 * @brief Construct a new circularly linked list, as well as a turn indicator and the text for each round
 * 
 */
Initiative::Initiative() : turnIndicator(15, 3)
{
    mHead = nullptr;
    mStart = mHead;
    round = 1;
    size = 0;

    turnIndicator.setFillColor(sf::Color::Black);
    turnIndicator.rotate(90);

    roundText.setCharacterSize(20);
    roundText.setFillColor(sf::Color::Black);
    roundText.setStyle(sf::Text::Bold);
    setRoundText();
}

/**
 * @brief Constructs a new circularly linked list based off of another list
 * 
 * @param copy List to be copied
 */
Initiative::Initiative(const Initiative &copy) : turnIndicator(15, 3)
{
    Node* copyPtr = copy.mHead;

    if(copy.mHead == nullptr)
    {
        mHead = nullptr;
        mStart = mHead;
        round = 1;
        size = 0;
    }
    else
    {
        mHead = nullptr;
        mStart = mHead;
        round = 1;
        size = 0;

        do
        {
            addNodeInOrder(copyPtr->character);
            copyPtr = copyPtr->next;
        }while(copyPtr != copy.mHead);
    }

    turnIndicator.setFillColor(sf::Color::Black);
    turnIndicator.rotate(90);

    roundText.setCharacterSize(20);
    roundText.setFillColor(sf::Color::Black);
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
 * @brief Saves the info in the list to a file. Designed to be paired with 
 *        other save functions, so does not close the file.
 * 
 * @param file File to save info to
 */
void Initiative::save(std::fstream &file)
{
    Node *ptr = mHead;

    if(ptr == nullptr) return;

    do
    {
        file << "-" << ptr->character.name << "," << ptr->character.health << ",";
        file << ptr->character.maxHealth << "," << ptr->character.tempHealth << ",";
        file << ptr->character.initiative << "," << ptr->character.armorClass << ",";
        file << ptr->character.status << "," << ptr->character.level << "\n";
        ptr = ptr->next;
    }while(ptr != mHead);
}

/**
 * @brief Loads the info from a file into a list. Designed to be paired with other
 *        load functions, so does not close the file.
 * 
 * @param file File to load info from
 */
void Initiative::load(std::fstream &file)
{
    char delim;
    std::string name, status;
    int health, maxHealth, tempHealth, initiative, armorClass, level;

    while(!file.eof())
    {
        file.get(delim);
        if(delim == '*') 
        {
            getline(file, name);
            break;
        }
        else
        {
            getline(file, name, ',');
            std::cout << name << " " << delim << "\n";
            file >> health >> delim;
            file >> maxHealth >> delim;
            file >> tempHealth >> delim;
            file >> initiative >> delim;
            file >> armorClass >> delim;
            getline(file, status, ',');
            file >> level;
            file.get(delim);

            Creature newCreature(name, maxHealth, health, tempHealth, initiative, armorClass, status, level);
            addNodeInOrder(newCreature);
        }
    }
}

/**
 * @brief Adds a new node to the list, sorted by initiative
 * 
 * @param character Creature object to be added
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
            if(character.initiative > ptr->character.initiative) found = true;
            else ptr = ptr->next;
        }while(ptr != mHead && !found);

        Node* nodePtr = new Node(character, ptr->prev, ptr);
        ptr->prev->next = nodePtr;
        ptr->prev = nodePtr;
        if(ptr == mHead && mHead->prev->character.initiative > mHead->character.initiative) mHead = mStart = ptr->prev;
        nodePtr->character.updateTextBoxes();
    }
    
    size++;
}

/**
 * @brief Deletes a specific node using the name to search by
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
        if(ptr == mHead) mHead = mStart = nullptr;  // potential error here
        delete ptr;
        ptr = nullptr;
    }

    size--;
}

/**
 * @brief Deletes a specific node based off of its position
 * 
 * @param mouseClick Position of node to be deleted
 */
void Initiative::deleteNode(const sf::Vector2f &mouseClick)
{
    Node *ptr = mHead;
    bool found = false;

    if(ptr == nullptr) return;

    do
    {
        if(ptr->character.isClicked(mouseClick)) found = true;
        else ptr = ptr->next;
    }while(ptr != mHead && !found);

    if(!found) return;

    // delete ptr
    if(mHead == ptr) mHead = mStart = mHead->next;
    ptr->prev->next = ptr->next;
    ptr->next->prev = ptr->prev;
    ptr->next = nullptr;
    ptr->prev = nullptr;
    if(mHead == ptr) mHead = mStart = nullptr;
    delete ptr;

    size--;
}

/**
 * @brief Deletes the node right before mHead
 * 
 */
void Initiative::deleteLast()
{
    Node *ptr = mHead;

    if(ptr == nullptr) return;

    ptr = mHead->prev;
    ptr->prev->next = mHead;
    ptr->next->prev = ptr->prev;

    ptr->next = nullptr;
    ptr->prev = nullptr;
    if(ptr == mHead)
    {
        mHead = nullptr;
        mStart = nullptr;
    }
    delete ptr;
    ptr = nullptr;

    size--;
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

    size += copy.size;
}

/**
 * @brief Deletes each node in the list
 * 
 */
void Initiative::clear()
{
    Node *ptr = mHead;
    if(ptr == nullptr) return;

    if(mHead->next != mHead)
    {
        ptr->prev->next = nullptr;
        ptr->next->prev = nullptr;
    }
    while(ptr != nullptr)
    {
        mHead = mHead->next;
        ptr->next = nullptr;
        ptr->prev = nullptr;
        if(mHead->next == nullptr) mHead = nullptr;
        delete ptr;
        ptr = mHead;
    }
    mHead = nullptr;
    mStart = nullptr;
    size = 0;
}

/**
 * @brief Sorts the entire list by initiative order. Stable
 * 
 */
void Initiative::sort()
{
    // if list is empty or has 1 element
    if(mHead == nullptr || mHead->next == mHead) return;

    Node *start = mHead->next;

    while(start != mHead)
    {
        Node *key = start;
        Node *index = start->prev;
        do
        {
            if(index->character.initiative < key->character.initiative)
            {
                // swap key and index
                if(index->next->next != index)
                {
                    index->next = key->next;
                    key->prev = index->prev;
                    index->prev->next = key;
                    key->next->prev = index;
                }
                index->prev = key;
                key->next = index;
                if(mHead == index) mHead = key;

                // decrement index and reset start
                index = index->prev->prev;
                if(start == key) start = start->next;
            }
        }while(index != mHead->prev && index->character.initiative < key->character.initiative);
        start = start->next;
    }
}

/**
 * @brief Returns the round counter
 * 
 * @return int Round the initiative is in
 */
int Initiative::getRound() const
{
    return round;
}

/**
 * @brief Returns a number based on how many nodes are in the list
 * 
 * @return int Size of the list
 */
int Initiative::getSize() const
{
    return size;
}

/**
 * @brief Returns a string containing all the levels/XP ratings of all the creatures.
          Returns an empty string if list is empty.
 * 
 * @return std::string Contains the levels of all the creatures in the list
 */
std::string Initiative::getLevel()
{
    ostringstream ostr;
    Node *ptr = mHead;

    if(ptr != nullptr)
    {
        do
        {
            ostr << ptr->character.getLevel() << " ";
            ptr = ptr->next;
        }while(ptr != mHead);
    }
    return ostr.str();
}

/**
 * @brief Returns the string from the textbox at a specific position
 * 
 * @param mouseClick Position of the textbox
 * @return std::string String of the textbox at the position. Empty 
 *                     if no textbox at that position.
 */
std::string Initiative::getString(sf::Vector2f &mouseClick)
{
    Node *ptr = mHead;
    std::string value;

    if(ptr != nullptr)
    {
        do
        {
            if(ptr->character.isClicked(mouseClick))
            {
                value = ptr->character.getString(mouseClick);
            }
            ptr = ptr->next;
        }while(ptr != mHead);
    }

    return value;
}

/**
 * @brief Gets the position of the first node in the list. Returns (0,0) if
 *        list is empty.
 * 
 * @return sf::Vector2f Position of the first textbox of the first node
 */
sf::Vector2f Initiative::getPosition() const
{
    sf::Vector2f pos(0, 0);
    
    if(mHead != nullptr) pos = mHead->character.nameText.getPosition();

    return pos;
}

/**
 * @brief Gets the name of the creature that is first in the list. If
 *        list is empty, returns "NA"
 * 
 * @return std::string Name of the first creature in the list, or "NA"
 */
std::string Initiative::getFirstName()
{
    std::string value = "NA";

    if(mHead != nullptr)
    {
        value = mHead->character.name;
    }

    return value;
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
 * @brief Updates the textbox at a certain position
 * 
 * @param x X coordinate of the position
 * @param y Y coordinate of the position
 * @param tempValue Value to update the string to
 */
void Initiative::edit(const float &x, const float &y, const std::string &tempValue)
{
    edit(sf::Vector2f(x, y), tempValue);
}

/**
 * @brief Updates the textbox at a certain position
 * 
 * @param mouseClick Position of textbox to be edited
 * @param tempValue Value to update the string to
 */
void Initiative::edit(const sf::Vector2f &mouseClick, const std::string &tempValue)
{
    Node *ptr = mHead;
    if(ptr != nullptr)
    {
        do
        {
            if(ptr->character.isClicked(mouseClick))
            {
                ptr->character.edit(mouseClick, tempValue);
            }
            ptr = ptr->next;
        }while(ptr != mHead);
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

    roundText.setFont(font);
    
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
 * @brief Sets the position of the linked list with a starting point in the top left corner. Position of the textboxes,
 *         round text, and the turn indicator are automatically set.
 * 
 * @param pos Starting point of the list
 */
void Initiative::setPosition(sf::Vector2f pos)
{
    sf::Vector2f curPos = pos;
    turnIndicator.setPosition(pos);
    
    Node* ptr = mHead;
    if(ptr != nullptr)
    {
        do
        {
            ptr->character.setPosition(pos);
            pos.y += 30;
            ptr = ptr->next;
        }while(ptr != mHead);
    }

    pos.y += 50;
    roundText.setPosition(curPos.x, pos.y);
}

 /**
  * @brief Sets the position of the linked list with a starting point in the top left corner. Position of the textboxes,
 *         round text, and the turn indicator are automatically set.
  * 
  * @param x Starting x coordiante of the list
  * @param y Starting y coordiante of the list
  */
void Initiative::setPosition(float x, float y)
{
    sf::Vector2f pos(x, y);
    setPosition(pos);
}

/**
 * @brief Sets the text object for the round with the actual round
 * 
 */
void Initiative::setRoundText()
{
    ostringstream ostr;
    ostr << "Round: " << round;
    roundText.setString(ostr.str());
}

/**
 * @brief Clears the texture from all nodes in the list
 * 
 */
void Initiative::clearTexture()
{
    Node *ptr = mHead;

    if(ptr != nullptr)
    {
        do
        {
            ptr->character.clearTexture();
            ptr = ptr->next;
        }while(ptr != mHead);
    }
}

/**
 * @brief Checks to see if a node was clicked
 * 
 * @param x X coordinate of mouse click
 * @param y Y coordinate of mouse click
 * @return true If a textbox in the nodes was clicked
 * @return false If no textbox in the nodes was clicked
 */
bool Initiative::isNodeClicked(const float &x, const float &y)
{
    return isNodeClicked(sf::Vector2f(x, y));
}

/**
 * @brief Checks to see if a node was clicked
 * 
 * @param mouseClick Position of the mouse click
 * @return true If a textbox in the nodes was clicked
 * @return false If no textbox in the nodes was clicked
 */
bool Initiative::isNodeClicked(const sf::Vector2f &mouseClick)
{
    Node* ptr = mHead;

    if(ptr != nullptr)
    {
        do
        {
            if(ptr->character.isClicked(mouseClick)) return true;
            else ptr = ptr->next;
        }while(ptr != mHead);
    }
    return false;
}

/**
 * @brief Advances the list in the turn order. Currently set up to return a string
 * 
 * @return string 
 */

/**
 * @brief Advances the mStart pointer to the next node in the list. If mStart is at the 
 *        head pointer, increment the round counter. Updates the position of the turn
 *        indicator to follow mStart.
 * 
 */
void Initiative::advanceTurn()
{
    if(mHead == nullptr) return;

    mStart = mStart->next;
    if(mStart == mHead) round++;
    setTurnIndicatorPosition();
    setRoundText();
}

/**
 * @brief Resets the start position to the beginning of the list. Resets the round and turn indicator
 * 
 */
void Initiative::resetStart()
{
    mStart = mHead;
    round = 1;
    setTurnIndicatorPosition();
}

/**
 * @brief Converts the contents of the list to a string
 * 
 * @return string Contains the contents of the list
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
 * @return string Contains the contents of the list
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
 * @return string Contains the contents of the list
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

/**
 * @brief Draws the list to the window for use in the initiative screen.
 *        Will draw the turn indicator, the round text, and not the levels of creatures.
 * 
 * @param window Window to be drawn to
 */
void Initiative::drawInitiativeList(sf::RenderWindow &window)
{
    Node* ptr = mHead;

    if(ptr != nullptr)
    {
        do
        {
            drawInitNode(window, ptr);
            ptr = ptr->next;
        }while(ptr != mHead);
    }

    window.draw(roundText);
    window.draw(turnIndicator);
}

/**
 * @brief Draws a specific node to the window for use in the initiative screen.
 * 
 * @param window Window to be drawn to.
 * @param ptr Pointer to a node that will be drawn
 */
void Initiative::drawInitNode(sf::RenderWindow &window, Node* &ptr)
{
    if(ptr != nullptr)
    {
        ptr->character.drawInit(window);
    }
}

/**
 * @brief Sets the position of the turn indicator to follow mStart
 * 
 */
void Initiative::setTurnIndicatorPosition()
{
    if(mStart == nullptr) return;
    sf::Vector2f currentPos = mStart->character.nameText.getPosition();
    turnIndicator.setPosition(currentPos);
}