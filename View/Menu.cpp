
#include "Menu.h"

Menu::Menu()
{
    this->qwirkle_msg = new std::string("");
    this->c = new char('c');
    this->isChar = new bool(false);
    this->statement = new std::regex("[1-4]");
    this->game_over = new bool(false);
    this->game = new Game();
};

Menu::~Menu()
{
    delete isChar;
    delete c;
    delete game_over;
    delete qwirkle_msg;
    delete statement;
};

// main menu
bool Menu::runMenu()
{

    // menu selection
    do
    {
        mainMenu();

        if (*c == '1')
        {
            prompt("Starting a New Game\n");
            game->newGame();
        }
        else if (*c == '2')
        {
            prompt("Load Game\n");
            game->loadGame();
        }
        else if (*c == '3')
        {
            prompt("Credits:\n");
            credits();
        }
        else if (*c == '4')
        {
            prompt("Quit\n");
            *game_over = true;
        }
        else
        {
            break;
        }
    } while (!*game_over);

    return *game_over;
};

// prints message
void Menu::prompt(std::string string)
{
    *qwirkle_msg = string;

    std::cout << *qwirkle_msg << std::endl;
};

// checks character was entered
bool Menu::getCharacter(char c)
{
if (std::cin.eof())
    {
        return true;
    }
    else
    {
        return false;
    }
    
};

void Menu::credits()
{
    prompt("Name: Tomas House\nStudent ID: s3858839\nEmail: s3858839@student.rmit.edu.au\n");
    prompt("Name: Karl Birk\nStudent ID: s3315632\nEmail: s3315632@student.rmit.edu.au\n");
    prompt("Name: Thomas Lambert\nStudent ID: s3632442\nEmail: s3632442@student.rmit.edu.au\n");
    prompt("Name: Gerard Kyan\nStudent ID: s3221311\nEmail: s3221311@student.rmit.edu.au");
    prompt("------------------------------------\n");
};

void Menu::mainMenu()
{
    do
    {
        // display menu
        prompt("Menu\n----\n1. New Game\n2. Load Game\n3. Credits (Show student information)\n4. Quit\n");
        std::cout << "> ";

        std::cin >> *c;

        *isChar = getCharacter(*c);

    } while (isChar && !std::regex_match(c, *statement));
}
