#ifndef ASSIGN2_NODE_H
#define ASSIGN2_NODE_H

#include "Tile.h"
#include <iostream>

class Node
{
public:
    Node();
    Node(Tile *n);
    ~Node();
    Tile *getData();
    Node *getNext();
    void setNext(Node *);
    void printData();

private:
    Tile* data;
    Node *next;
};

#endif // ASSIGN2_NODE_H
