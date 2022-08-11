

#include "Tile.h"

Tile::Tile()
{

    colour = Colour();
    shape = Shape();
};

Tile::Tile(Colour c, Shape s)
{
    shape = Shape(s);
    colour = Colour(c);
};

Tile::~Tile(){

};
Colour Tile::getColour()
{
    return this->colour;
};
Shape Tile::getShape()
{
    return this->shape;
};
void Tile::printColourAndShape()
{

    if (this->colour == 'R')
        std::cout << "RED    : R";
    else if (this->colour == 'O')
        std::cout << "ORANGE : O";
    else if (this->colour == 'Y')
        std::cout << "YELLOW : Y";
    else if (this->colour == 'G')
        std::cout << "GREEN  : G";
    else if (this->colour == 'B')
        std::cout << "BLUE   : B";
    else if (this->colour == 'P')
        std::cout << "PURPLE : P";
    if (this->shape == 1)
        std::cout << "1 : CIRCLE";
    else if (this->shape == 2)
        std::cout << "2 : STAR 4";
    else if (this->shape == 3)
        std::cout << "3 : DIAMOND";
    else if (this->shape == 4)
        std::cout << "4 : SQUARE";
    else if (this->shape == 5)
        std::cout << "5 : STAR 6";
    else if (this->shape == 6)
        std::cout << "6 : CLOVER";
};
