#ifndef ASSIGN2_GAME_H
#define ASSIGN2_GAME_H

#include <iostream>
#include <memory>
#include <string>
#include <regex>
#include <vector>
#include <sstream>
#include <random>


#include "../Model/TileCodes.h"
#include "../Model/Tile.h"
#include "../Model/Board.h"
#include "../Model/Player.h"
#include "Validation.h"
#include "DataHandler.h"
#include "ScoringSystem.h"

const int MAX_TILES = 72;
const int ASCII_ALPHABET_OFFSET = 65;
const int ASCII_NUMERIC_OFFSET = 48;
const int handTilecount = 6;
const int ROW_COUNT = 26;
const int COL_COUNT = 26;
const char SPACE = ' ';
const char DASH = '-';
const char PIPE = '|';
const int MINPLAYERS = 2;

class Game
{
public:
    Game();
    ~Game();
    std::string getBoardAsString();
    bool newGame();
    bool loadGame();
    Player getCurentPlayer();
    std::vector<std::string> tokeniseInput();
    void selectNumPlayers();
    char getNumToPlay();
    void setNumToPlay(char numToPlay);
    

private:
    Player *player1;
    Player *player2;
    Player *player3;
    Player *player4;
    Player *currentPlayer;
    Board *board;
    bool *itIsPlayer1s_turn;
    LinkedList *bag;
    Validation *validation;
    ScoringSystem *scoringSystem;
    Tile *tempTile;
    LinkedList *hand;
    bool nextTurn = true;
    char *numToPlay;
    int nextPlayer = 1;

    
    
    

    std::string *c;
    bool *isChar;
    std::regex *statement;
    bool getCharacter(char);

    void saveGame(std::string *&filename);
    bool play();
    void exit();
    void prompt_invalidInput();
    void fillBagAndShuffle();
    void printHand(Player *&);
    void printScores();
    void printBoard();
    void promptForPlayInput();
    void printCurrentPlayer(Player *&);
    bool takeTurn(Player *&);
    bool checkEndGameConditions(Player *&);
    void printBagTileCount();
    std::string getUserInput();
    std::string getUserInput(int index);
    void setupNewPlayers();
    bool validateInput(Validation validation);
    
};  

#endif // ASSIGN2_GAME_H