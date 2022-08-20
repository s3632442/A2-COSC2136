#ifndef ASSIGN2_DATAHANDLER_H
#define ASSIGN2_DATAHANDLER_H

#include <iostream>
#include <fstream>
#include <string>
#include "Game.h"
#include "../Model/Board.h"
#include "../Model/Player.h"
#include "../Model/LinkedList.h"


class DataHandler
{
public:
    DataHandler();
    ~DataHandler();
    bool loadData(std::string);
    bool saveData();
    void setPlayer1(Player *&player1);
    void setPlayer2(Player *&player2);
    void setBoard(Board *&board);
    void setBag(LinkedList *&bag);
    void setCurrentPlayerName(std::string *&currentPlayerName);
    void setFilename(std::string *&filename);
    std::string getPlayer1Name();
    std::string getPlayer2Name();
    void fillBagWithSavedTiles(LinkedList *&bag);
    int getPlayer1Score();
    int getPlayer2Score();
    void fillPlayer2HandWithSavedTiles(LinkedList *&);
    void fillPlayer1HandWithSavedTiles(LinkedList *&);
    int getBoardHeight();
    int getBoardWidth();
    std::string getCurrentPlayerName();
    Board getBoard();
    

private:
    std::string *gameState;
    std::string *filename;
    std::string *currentPlayerName;
    LinkedList *bag;
    Board *board;
    Player *player1;
    Player *player2;
    Player *player3;
    Player *player4;
    std::string handAsString(Player *&);
    std::string boardShapeAsString(Board *&board);
    std::string setBoardStateAsString(Board *&board);
    std::string bagContentsAsString(LinkedList *&bag);
};

#endif // ASSIGN2_DATAHANDLER_H