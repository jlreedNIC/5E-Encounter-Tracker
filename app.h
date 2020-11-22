#ifndef APP_H
#define APP_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include "button.h"
#include "textbox.h"
#include "initiativelist.h"
#include "encounter.h"

class App
{
    public:
        App();
        ~App();

        bool appIsOpen();

        void mainMenu();

        void initiative();

        void editNode(Initiative& initList, const float &x, const float &y);

    private:
        sf::RenderWindow window;
        Encounter encounter;

        sf::Text saves[3];  // change to textbox

        sf::Font headerFont;
        sf::Font buttonFont;
        
        sf::Texture buttonTexture;

        // buttons
        Button newEncounter;
        Button loadEncounter;
        Button initiativeButton;
        Button exitButton;
        sf::Text headerText;

        // helper functions
        void mainMenuInput();
        void mainMenuUpdate();
        void mainMenuDraw();

        void loadSave();
        void newSave();
};

#endif