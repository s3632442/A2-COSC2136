#ifndef ASSIGN2_MENU_H
#define ASSIGN2_MENU_H

/**
 * @file Menu.h
 * @author your name (you@domain.com)
 * @brief CUI menus, to navigate Qwirkle's dev team credits, launch a New Game 
 * or Load Saved Games;
 * @version 0.1
 * @date 2022-08-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <regex>
#include <string>


#include "../Model/Node.h"
#include "../Model/LinkedList.h"
#include "../Model/Node.h"
#include "../Model/Player.h"
#include "../Controller/Game.h"

class Menu
{
public:
    Menu();
    ~Menu();

    std::string *qwirkle_msg;
    char *c;
    bool *isChar;
    std::regex *statement;
    bool *game_over;
    std::string user_input;
    

    void prompt(std::string);
    bool getCharacter(char);
    bool runMenu();
    void credits();
    void mainMenu();
    void help();
    void rules();

private:
    Game* game;
};
#endif