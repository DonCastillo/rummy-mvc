#include "Player.h"
#include <iostream>

void Player::addCard(Card* c)
{
    hand.push_back(c);
}

list<Card*>* Player::getHand()
{
    return &hand;
}

Card* Player::getCard(unsigned int index){
    if(index >= hand.size() || index < 0)
        return nullptr;

    list<Card*>::iterator card;
    unsigned int count = 0;
    for(card = hand.begin(); card != hand.end() && count < index; ++card){
            count++;
    }
    return *card;
}

void Player::addPoints(unsigned int points){
    score += points;
}

unsigned int Player::getScore(){
    return score;
}
