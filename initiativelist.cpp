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
    size = 0;

    for(int i=0; i<6; i++)
    {
        headers[i].setCharacterSize(20);
        headers[i].setStyle(sf::Text::Bold);
        headers[i].setFillColor(sf::Color::Black);
    }

    headers[0].setString("Name");
    headers[1].setString("Initiative");
    headers[2].setString("AC");
    headers[3].setString("Health");
    headers[4].setString("Temp HP");
    headers[5].setString("Status/Notes");

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
Initiative::Initiative(const Initiative &copy)
{
    Node* copyPtr = copy.mHead;

    if(copy.mHead == nullptr)
    {
        mHead = nullptr;
        mStart = mHead;
        round = 0;
        size = 0;
    }
    else
    {
        mHead = nullptr;
        mStart = mHead;
        round = 0;
        size = 0;

        do
        {
            addNodeInOrder(copyPtr->character);
            copyPtr = copyPtr->next;
        }while(copyPtr != copy.mHead);
    }

    for(int i=0; i<6; i++)
    {
        headers[i].setCharacterSize(20);
        headers[i].setStyle(sf::Text::Bold);
        headers[i].setFillColor(sf::Color::Black);
    }

    headers[0].setString("Name");
    headers[1].setString("Initiative");
    headers[2].setString("AC");
    headers[3].setString("Health");
    headers[4].setString("Temp HP");
    headers[5].setString("Status/Notes");

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
    
    size++;
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
        if(ptr == mHead) mHead = mStart = nullptr;  // potential error here
        delete ptr;
        ptr = nullptr;
    }

    size--;
}

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

void Initiative::clear()
{
    Node *ptr = mHead;
    Node *prevPtr = ptr;

    if(ptr != nullptr)
    {
        do
        {
            ptr = ptr->next;
            deleteNode(prevPtr->character.name);
            prevPtr = ptr;
        }while(ptr != nullptr && ptr != mHead);
    }
    ptr = prevPtr = mHead = nullptr;
    round = 0;
    mStart = nullptr;
}

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
 * @return int 
 */
int Initiative::getRound() const
{
    return round;
}

int Initiative::getSize() const
{
    return size;
}

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

// TextBox& Initiative::getTextBox(const float &x, const float &y)
// {
//     Node *ptr = mHead;
//     if(mHead != nullptr)
//     {
//         do
//         {
//             if(ptr->character.isClicked(x, y)) 
//                 return ptr->character.getTextBox(x, y);
//             else ptr = ptr->next;
//         }while(ptr != mHead);
//     }
// }

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

sf::Vector2f Initiative::getPosition() const
{
    return mHead->character.nameText.getPosition();
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

void Initiative::edit(const float &x, const float &y, const std::string &tempValue)
{
    edit(sf::Vector2f(x, y), tempValue);
}

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

    for(int i=0; i<6; i++)
        headers[i].setFont(font);

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
 * @brief Sets the position of the linked list with a starting point in the top left corner. Position of the headers and textboxes
 *        are automatically set.
 * 
 * @param pos Starting point of the list
 */
void Initiative::setPosition(sf::Vector2f pos)
{
    sf::Vector2f curPos = pos;
    headers[0].setPosition(pos.x, pos.y);
    headers[1].setPosition(pos.x + 100, pos.y);
    headers[2].setPosition(pos.x + 200, pos.y);
    headers[3].setPosition(pos.x + 250, pos.y);
    headers[4].setPosition(pos.x + 325, pos.y);
    headers[5].setPosition(pos.x + 425, pos.y);
    
    Node* ptr = mHead;
    if(ptr != nullptr)
    {
        do
        {
            ptr->character.setPosition(pos);
            pos.y += 35;
            ptr = ptr->next;
        }while(ptr != mHead);
    }

    pos.y += 50;
    roundText.setPosition(curPos.x, pos.y);
}

 /**
  * @brief Sets the position of the linked list with a starting point in the top left corner. Position of the headers and textboxes
  *        are automatically set.
  * 
  * @param x Starting x coordiante of the list
  * @param y Starting y coordiante of the list
  */
void Initiative::setPosition(float x, float y)
{
    sf::Vector2f pos(x, y);
    setPosition(pos);
}

void Initiative::setRoundText()
{
    ostringstream ostr;
    ostr << "Round: " << round;
    roundText.setString(ostr.str());
}

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

bool Initiative::isNodeClicked(const float &x, const float &y)
{
    return isNodeClicked(sf::Vector2f(x, y));
}

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

    // for(int i=0; i<6; i++)
    //     window.draw(headers[i]);

    if(ptr != nullptr)
    {
        do
        {
            drawNode(window, ptr);
            ptr = ptr->next;
        }while(ptr != mHead);
    }

    // window.draw(roundText);
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