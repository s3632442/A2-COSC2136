

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
        std::cout << "RED";
    else if (this->colour == 'O')
        std::cout << "ORANGE";
    else if (this->colour == 'Y')
        std::cout << "YELLOW";
    else if (this->colour == 'G')
        std::cout << "GREEN";
    else if (this->colour == 'B')
        std::cout << "BLUE";
    else if (this->colour == 'P')
        std::cout << "PURPLE";
    std::cout << " : ";
    if (this->shape == 1)
        std::cout << "CIRCLE";
    else if (this->shape == 2)
        std::cout << "STAR 4";
    else if (this->shape == 3)
        std::cout << "DIAMOND";
    else if (this->shape == 4)
        std::cout << "SQUARE";
    else if (this->shape == 5)
        std::cout << "STAR 6";
    else if (this->shape == 6)
        std::cout << "CLOVER";
};
