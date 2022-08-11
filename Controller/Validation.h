#ifndef ASSIGN2_VALIDATION_H
#define ASSIGN2_VALIDATION_H
#include "../Model/Tile.h"
#include "../Model/LinkedList.h"
#include "../Model/Board.h"

class Validation
{

public:
    Validation();
    ~Validation();

    bool setInput();
    void getInput();
    // test in game.cpp newGame();
    bool validateInputLength(int);
    // called from checkEmptySpace()
    bool inputWithinBounds(char, int);
    // test in game.cpp newGame();
    // see if tile in hand
    bool validateTileChosen(LinkedList *, Tile *);
    // see if space is empty before trying to validate move by game rules
    bool checkEmptySpace(Tile*, Board *, int, int);
    // test in qwirkle.cpp
    // gets input from user as a string, string is used to make a file object and try to open this file.
    // if file cannot be read then the file doesnt exist and false is returned
    bool checkFileExists(std::string);
    // test in qwirkle.cpp
    // name needs to be uppercase, only letters, no numbers or symbols
    bool playerNameValid(std::string &);
    // validates the user input for a valid board position
    bool validateInputProposed(Tile*, Board *, std::string);
    // validateMove will check surrounding tiles to follow game rules
    bool validateMove(Board *, int, int, bool, Tile *);
    bool validateNorth(Board *, int, int, Tile *);
    bool validateEast(Board *, int, int, Tile *);
    bool validateSouth(Board *, int, int, Tile *);
    bool validateWest(Board *, int, int, Tile *);
    bool checkAdjacentTilesRowLength(Board *, int, int);

private:
    Tile tilePlayed;
    char userInput[5];
    bool checkBoardIsEmpty(Board *boardPointer);
};
#endif // ASSIGN2_VALIDATION_H