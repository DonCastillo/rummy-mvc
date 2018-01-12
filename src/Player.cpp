#include "Player.h"

void Player::addCard(Card* c)
{
    hand.push_back(c);
}

Card* Player::getPlay(int (*playPrompt)())
{
    int index = playPrompt();
    return hand[index];
}
