#ifndef PLAYER_H
#define PLAYER_H

using namespace std;

#include <string>
#include <vector>
#include "Card.h"

class Player
{
    public:
        Player(string n) : name(n) {}
        virtual ~Player() {}
        void addCard(Card* c);
        Card* getPlay(int (*playPrompt)());

    protected:

    private:
        string name;
        vector<Card*> hand;
};

#endif // PLAYER_H
