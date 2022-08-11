#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H

#include "LinkedList.h"
#include <iostream>

class Player
{
public:
    Player();
    Player(std::string name, int score);
    ~Player();

    std::string getName();
    int getScore();
    void addToScore(int);
    void printName();
    void printScore();
    void setName(std::string);
    Player(Player &other);
    LinkedList* getHand();
    //void setHand(LinkedList* hand);
    std::string getHandAsString();
    void setScore(int);

private:
    std::string name;
    int score;
    LinkedList* hand;
};

#endif // ASSIGN2_PLAYER_H