#include <string>
#include "Board.h"

Board::Board(int height, int width)
{
    tiles2DVector = std::vector<std::vector<Tile *> >(height, std::vector<Tile *>(width, nullptr));
}

Board::~Board()
{
}

void Board::placeTileAt(Tile *tile, int row, int column)
{
    Colour colour = tile->getColour();
    Shape shape = tile->getShape();

    Tile *newTile = new Tile(colour, shape);
    tiles2DVector[row][column] = newTile;
}

Tile *Board::getTileAt(int row, int column)
{
    return this->tiles2DVector[row][column];
}

std::vector<std::vector<Tile *> > Board::getTiles2DVector()
{
    return this->tiles2DVector;
}
