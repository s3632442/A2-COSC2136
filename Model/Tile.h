#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include "TileCodes.h"
#include <iostream>

// Define a Colour type
typedef char Colour;

// Define a Shape type
typedef int Shape;

class Tile
{
public:
    Tile();
    Tile(Colour c, Shape s);
    ~Tile();
    Colour getColour();
    Shape getShape();
    void printColourAndShape();

private:
    Colour colour;
    Shape shape;
};

#endif // ASSIGN2_TILE_H