#ifndef ASSIGN2_BOARD_H
#define ASSIGN2_BOARD_H

#include <iostream>
#include <vector>
#include "Tile.h"

class Board
{
public:
    Board(int height, int width);
    ~Board();
    std::vector<std::vector<Tile *> > getTiles2DVector();
    void placeTileAt(Tile *tile, int row, int column);
    Tile* getTileAt(int row, int column);
    void setHeightWidth(int height, int width);
    private :
        // 2D Vector, for now
        // 20220712
        // https://www.geeksforgeeks.org/initialize-a-vector-in-cpp-different-ways/
        // https://stackoverflow.com/questions/17663186/initializing-a-two-dimensional-stdvector
        std::vector<std::vector<Tile *> >
            tiles2DVector;
};

#endif // ASSIGN2_BOARD_H