#include "Cheat.h"

#include <iostream>

void Cheat::dealCards(vector<Player*> p)
{
    unsigned int playerNum = 0;
    unsigned int numCards;
    while(deck->size() > 0)
    {
        //cout << "Deck Size: " << deck->size() << endl;
        Player* p = players.at(playerNum);
        p->addCard(deck->getCard());
        playerNum = ++playerNum % players.size();
    }
}

void Cheat::beforeCardPlayed(unsigned int playerNum, unsigned int numPlayers) {}

void Cheat::afterCardPlayed(Player* currentPlayer, vector<Player*> players, Card* played) {}
