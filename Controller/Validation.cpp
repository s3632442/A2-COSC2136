#include "Validation.h"
#include <algorithm>
#include <regex>
#include <fstream>
#include <iostream>
#include <string>
Validation::Validation()
{
}

Validation::~Validation()
{
}

bool Validation::validateTileChosen(LinkedList *playerHand, Tile *proposedTile)
{
    bool allowed = false;
    std::cout << "Proposed Tile: " << proposedTile->getColour() << proposedTile->getShape() << std::endl;
    Node *temp = (*playerHand).getHead();

    if (temp != NULL)
    {
        // going through hand to see if proposed tile is in the hand
        while (temp != NULL)
        {
            if (temp->getData()->getColour() == proposedTile->getColour() && temp->getData()->getShape() == proposedTile->getShape())
            {
                std::cout << "Tile in Hand" << std::endl;

                allowed = true;
            }
            else
            {

                std::cout << "Temp: " << temp->getData()->getColour() << temp->getData()->getShape() << std::endl;
                temp = temp->getNext();
            }
        }
    }
    std::cout << "Tile Not in Hand" << std::endl;
    return allowed;
};
bool Validation::playerNameValid(std::string &name)
{
    bool isAllowed = true;
    if (name.empty())
    {
        // std::cout << "Name Empty" << std::endl;
        isAllowed = false;
    }
    else
    {
        char c;
        // Iterate through the string one letter at a time.
        for (int i = 0; i < name.length(); i++)
        {

            c = name.at(i);

            // if it's NOT within these bounds, then it's not a valid character
            if (!((c >= 'A' && c <= 'Z')))
            {

                // std::cout << "Please use uppercase characters only" << std::endl;

                isAllowed = false;
            }
        }
    }

    // std::cout << "Name Valid" << std::endl;
    return isAllowed;
};

// check to see if the position is filled

bool Validation::checkEmptySpace(Tile *tile, Board *boardPointer, int rowAsInt, int column)
{

    // If we get here position input is valid and now we check for empty space

    bool isEmptySpace = false;

    bool isEmptyBoard = false;

    isEmptyBoard = checkBoardIsEmpty(boardPointer);

    // adding tiles to board to test
    // remove before use of method in real game
    // Tile *t = new Tile('R', 4);
    // Tile *t2 = new Tile('R', 2);
    // Tile *t3 = new Tile('R', 3);

    // boardPointer->placeTileAt(t, 1, 1);

    // rowAsInt-1 makes the row fall between elements 0 and 25. Otherwise rowAsInt for Z would be 26 and out of bounds for 2D vector
    // A is element 0 but rowAsInt(A) would =1
    if (boardPointer->getTileAt(rowAsInt, column) == nullptr)
    {
        char rowAsChar = rowAsInt + 65;
        //std::cout << "tile is empty at: " << rowAsChar << column << std::endl;
        //std::cout << "*now could place tile, if in hand, and valid tiles around it*" << std::endl;
        // validateMove will check surrounding tiles to follow game rules
        // this needs to be called from game, need to rework the return values so that methods in this class dont
        // call other methods

        isEmptySpace = validateMove(boardPointer, rowAsInt, column, isEmptyBoard, tile);
    }
    else
    {
        //std::cout << "tile is full" << std::endl;
        isEmptySpace = false;
    }

    //std::cout << "Validation::checkEmptySpace() returns " << isEmptySpace << std::endl;

    return isEmptySpace;
};

bool Validation::checkFileExists(std::string fileName)
{
    bool fileExists = false;
    std::ifstream file;
    file.open(fileName);
    if (file)
    {
        //std::cout << "file exists" << std::endl;
        fileExists = true;
    }
    else
    {
        //std::cout << "file doesn't exist" << std::endl;
        fileExists = false;
    }

    return fileExists;
};

// if the requested space on board is within bounds return true, else false
bool Validation::inputWithinBounds(char row, int col)
{
    bool withinBounds = false;
    if (((row >= 'A' && row <= 'Z')) && (col >= 0 && col <= 25))
    {
        withinBounds = true;
    }
    else
    {
        withinBounds = false;
    }
    return withinBounds;
};

bool Validation::validateInputLength(int wordCount)
{
    bool wordCountIsValid = true;

    if (wordCount == 4 || wordCount == 2)
    {
        wordCountIsValid = true;
    }
    else
    {
        wordCountIsValid = false;
    }

    return wordCountIsValid;
};

bool Validation::validateMove(Board *boardPointer, int targetRow, int targetColumn, bool firstMoveOfGame, Tile *tileProposed)
{
    // need to check up, down,left and right and look for valid placements of tile
    int rowElement = targetRow;
    //std::cout << "Validation::validateMove targetRow: " << rowElement << std::endl;
    int columnElement = targetColumn;
    //std::cout << "Validation::validateMove targetColumn: " << columnElement << std::endl;
    int truths = 0;
    int falses = 0;

    bool validity = false;
    int adjacentTiles = 0;
    bool firstMove = firstMoveOfGame;
    if (firstMove == true)
    {
        validity = true;
        // if this happens the variable of firstMoveOfGame in game.h/cpp needs to change to false
        // therefore next validateMove() we will go into the else statement
    }
    else
    {
        //std::cout << rowElement << "  " << columnElement << std::endl;
        // check adjacent tiles for valid move following rules
        // if all adjacent tiles to proposed position are empty, you cannot place here (unless first move of game)
        if (boardPointer->getTileAt(rowElement, columnElement + 1) == nullptr &&
            boardPointer->getTileAt(rowElement, columnElement - 1) == nullptr &&
            boardPointer->getTileAt(rowElement - 1, columnElement) == nullptr &&
            boardPointer->getTileAt(rowElement + 1, columnElement) == nullptr)

        {
            std::cout << "Cannot place where there is no adjacent tile (unless on first move)" << std::endl;
            validity = false;
        }
        else
        {
            if (validateNorth(boardPointer, rowElement, columnElement, tileProposed))
            {
                truths++;
                //std::cout << "Validate north true" << std::endl;
            }
            else
            {
                falses++;
            }

            if (validateSouth(boardPointer, rowElement, columnElement, tileProposed))
            {
                truths++;
                //std::cout << "Validate south true" << std::endl;
            }
            else
            {
                falses++;
            }

            if (validateEast(boardPointer, rowElement, columnElement, tileProposed))
            {
                truths++;
                //std::cout << "Validate east true" << std::endl;
            }
            else
            {
                falses++;
            }

            if (validateWest(boardPointer, rowElement, columnElement, tileProposed))
            {
                truths++;
                //std::cout << "Validate west true" << std::endl;
            }
            else
            {
                falses++;
            }

            //std::cout << "truths: " << truths << std::endl;
            //std::cout << "falses: " << falses << std::endl;

            if (falses > 0)
            {
                //std::cout << "Cannot place tile" << std::endl;
                validity = false;
            }
            else
            {
                // Let Game.cpp do the placeTileAt.
                //boardPointer->placeTileAt(tileProposed, rowElement, columnElement);
                validity = true;
            }
        }
    }

    //std::cout << "Validation::validateMove() returns " << validity << std::endl;
    return validity;
}

bool Validation::validateInputProposed(Tile *tile, Board *boardPointer, std::string positionRequested)
{
    bool allowed = true;

    std::string columnAsString = "";
    char row;
    int column;
    int length = 0;
    for (int i = 0; positionRequested[i] != '\0'; i++)
    {
        length++;
    }
    // ie length of input must be 3. Example 'B15' or 'G23'
    if (length == 3)
    {
        //std::cout << "Position Requested Row:" << positionRequested[0] << std::endl;
        //std::cout << "Position Requested Col:" << positionRequested[1] << positionRequested[2] << std::endl;
        row = positionRequested[0];
        if (isalpha(row))
        {
            // std::cout<<"Row: "<<row<<" is a char"<<std::endl;
        }
        else
        {
            // std::cout<<"Row: "<<row<<" is not a char"<<std::endl;
            allowed = false;
        }

        if (isdigit(positionRequested[1]) && isdigit(positionRequested[2]))
        {
            columnAsString.append(positionRequested, 1, 2);
            // std::cout<<"Column: "<<columnAsString<<" is a number"<<std::endl;
        }
        else
        {
            // std::cout<<"Column: "<<columnAsString<<" is not a number"<<std::endl;
            allowed = false;
        }
        // ie length of input must be 2. Example 'B7' or 'Z4'
    }
    else
    {
        //std::cout << "Position Requested Row:" << positionRequested[0] << std::endl;
        //std::cout << "Position Requested Col:" << positionRequested[1] << std::endl;
        row = positionRequested[0];
        if (isalpha(row))
        {
            // std::cout<<"Row: "<<row<<" is a char"<<std::endl;
        }
        else
        {
            // std::cout<<"Row: "<<row<<" is not a char"<<std::endl;
            allowed = false;
        }
        if (isdigit(positionRequested[1]))
        {
            columnAsString.append(positionRequested, 1, 1);
            // std::cout<<"Column: "<<columnAsString<<" is a number"<<std::endl;
        }
        else
        {
            // std::cout<<"Column: "<<columnAsString<<" is not a number"<<std::endl;
            allowed = false;
        }
    }
    // converting row char to number so we can use it in 2d vector as an element
    int rowAsInt = (row - 65);
    //std::cout << "row as int: " << rowAsInt << std::endl;
    // converting columnAsString which is string into int for column
    column = std::stoi(columnAsString);
    if (inputWithinBounds(row, column))
    {
        //std::cout << "TRUE: input within bounds" << std::endl;
    }
    else
    {
        //std::cout << "FALSE: input out of bounds" << std::endl;
        allowed = false;
    }

    allowed = checkEmptySpace(tile, boardPointer, rowAsInt, column);

    return allowed;
}
// if position of N,E,S or W of target position is empty or matching of tileProposed charachteristics then return true
// if position of N,E,S or W of target position is not empty and doesnt match charachteristics, return false
bool Validation::validateNorth(Board *boardPointer, int targetRow, int targetColumn, Tile *tileProposed)
{
    Colour colour = tileProposed->getColour();
    Shape shape = tileProposed->getShape();
    //std::cout << "targetRow: " << targetRow << std::endl;    // target row 13
    //std::cout << "targetCol: " << targetColumn << std::endl; // target col 10
    char rowChar = targetRow + 65;
    // char colChar = targetColumn+48;
    //std::cout << "Validation::validateNorth() tileProposed: " << colour << shape << std::endl; // accurate
    //std::cout << "at targetRowColumn: " << rowChar << targetColumn << std::endl;
    // std::cout << "at targetRow: " << targetRow + 48 << std::endl;

    bool isAllowed = false;
    if (boardPointer->getTileAt(targetRow + 1, targetColumn) != nullptr)
    {
        if (tileProposed->getColour() == boardPointer->getTileAt(targetRow + 1, targetColumn)->getColour() ||
            tileProposed->getShape() == boardPointer->getTileAt(targetRow + 1, targetColumn)->getShape())
        {
            isAllowed = true;
        }
        else
        {
            isAllowed = false;
        }
    }
    else
    {
        // if north tile is nullptr then return true
        isAllowed = true;
    }

    return isAllowed;
};

bool Validation::validateEast(Board *boardPointer, int targetRow, int targetColumn, Tile *tileProposed)
{
    bool isAllowed = false;
    if (boardPointer->getTileAt(targetRow, targetColumn + 1) != nullptr)
    {
        if (tileProposed->getColour() == boardPointer->getTileAt(targetRow, targetColumn + 1)->getColour() ||
            tileProposed->getShape() == boardPointer->getTileAt(targetRow, targetColumn + 1)->getShape())
        {
            isAllowed = true;
        }
        else
        {
            isAllowed = false;
        }
    }
    else
    {
        // if east tile is nullptr then return true
        isAllowed = true;
    }

    return isAllowed;
};

bool Validation::validateSouth(Board *boardPointer, int targetRow, int targetColumn, Tile *tileProposed)
{
    bool isAllowed = false;
    if (boardPointer->getTileAt(targetRow - 1, targetColumn) != nullptr)
    {
        if (tileProposed->getColour() == boardPointer->getTileAt(targetRow - 1, targetColumn)->getColour() ||
            tileProposed->getShape() == boardPointer->getTileAt(targetRow - 1, targetColumn)->getShape())
        {
            isAllowed = true;
        }
        else
        {
            isAllowed = false;
        }
    }
    else
    {
        // if south tile is nullptr then return true
        isAllowed = true;
    }
    return isAllowed;
};

bool Validation::validateWest(Board *boardPointer, int targetRow, int targetColumn, Tile *tileProposed)
{
    bool isAllowed = false;
    if (boardPointer->getTileAt(targetRow, targetColumn - 1) != nullptr)
    {
        if (tileProposed->getColour() == boardPointer->getTileAt(targetRow, targetColumn - 1)->getColour() ||
            tileProposed->getShape() == boardPointer->getTileAt(targetRow, targetColumn - 1)->getShape())
        {
            isAllowed = true;
        }
        else
        {
            isAllowed = false;
        }
    }
    else
    {
        // if west tile is nullptr then return true
        isAllowed = true;
    }
    return isAllowed;
};

bool Validation::checkAdjacentTilesRowLength(Board *board, int row, int column)
{
    bool lengthIsAllowed = true;

    int rowToCheck = row - 1;
    int columnToCheck = column;
    int northAndSouthRowLength = 0;
    int eastAndWestRowLength = 0;

    while (board->getTileAt(rowToCheck, columnToCheck + 1) != nullptr && columnToCheck <= 25 && columnToCheck >= 0)
    {

        northAndSouthRowLength++;
        columnToCheck++;
    }
    while (board->getTileAt(rowToCheck, columnToCheck - 1) != nullptr && columnToCheck <= 25 && columnToCheck >= 0)
    {

        northAndSouthRowLength++;
        columnToCheck--;
    }
    while (board->getTileAt(rowToCheck + 1, columnToCheck) != nullptr && rowToCheck <= 25 && rowToCheck >= 0)
    {

        eastAndWestRowLength++;
        rowToCheck++;
    }
    while (board->getTileAt(rowToCheck - 1, columnToCheck) != nullptr && rowToCheck <= 25 && rowToCheck >= 0)
    {

        eastAndWestRowLength++;
        rowToCheck--;
    }
    if (northAndSouthRowLength == 6 || eastAndWestRowLength == 6)
    {
        std::cout << "cannot place tile at Row: " << row << " Column: " << column << std::endl;
        lengthIsAllowed = false;
    }

    return lengthIsAllowed;
};


bool Validation::checkBoardIsEmpty(Board *boardPointer)
{
    bool boardIsEmpty = true;
    int rowCount = boardPointer->getTiles2DVector().size();
    for (int row = 0; row < rowCount; row++)
    {
        int colCount = boardPointer->getTiles2DVector().at(row).size();
        for (int column = 0; column < colCount; column++)
        {
            if (boardPointer->getTileAt(row, column) != nullptr)
            {
                boardIsEmpty = false;
            }
        }
    }

    return boardIsEmpty;
}