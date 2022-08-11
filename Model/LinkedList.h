#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H
#include <iostream>
#include "Node.h"

class LinkedList
{
public:
    LinkedList();
    ~LinkedList();
    void addEnd(Tile *n);
    void printAll();
    void removeEnd();
    void addFront(Tile *n);
    Tile *removeFront();
    bool nodeExists(Tile);
    int frequency(Tile *);
    int getLength();
    Node *getNodeByData(Tile);
    Node *getNodeByIndex(int);
    void removeNodeAtIndex(int);
    // void removeNodeContaining(Tile);
    void removeNodeContaining(Tile*&);
    Node *getHead();

private:
    Node *head;
    Node *tail;
    int length;
};

#endif