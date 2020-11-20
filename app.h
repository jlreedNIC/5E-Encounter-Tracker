#ifndef APP_H
#define APP_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include "button.h"
#include "textbox.h"
#include "initiativelist.h"

class App
{
    public:
        App();
        ~App();

        bool appIsOpen();

        void mainMenu();

        void initiative();

        

    private:
        sf::RenderWindow window;
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