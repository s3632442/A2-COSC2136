#include "Player.h"

Player::Player()
{
    this->hand = new LinkedList();
    this->name = std::string();
    this->score = int();
};

Player::Player(std::string n, int s)
{
    this->name = n;
    this->score = s;
};

Player::~Player(){

};

std::string Player::getName()
{
    return this->name;
};

int Player::getScore()
{
    return this->score;
};

void Player::addToScore(int p)
{
    this->score += p;
};
void Player::printName()
{
    std::cout << this->name;
};

void Player::printScore()
{
    std::cout << this->score;
};

void Player::setName(std::string n)
{
    this->name = n;
};

LinkedList* Player::getHand()
{
    return hand;
}


void Player::setHand(LinkedList* h)
{
    this->hand = h;
}


std::string Player::getHandAsString()
{
    std::string handAsString = "";
    return handAsString;
}

void Player::setScore(int score)
{
    this->score = score;
}
