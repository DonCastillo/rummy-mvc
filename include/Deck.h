#ifndef DECK_H
#define DECK_H

using namespace std;

#include "Card.h"
#include <list>

class Deck
{
    public:
        Deck();
        virtual ~Deck(){}
        void shuffle();
        Card* getCard();
        unsigned int size();

    protected:

    private:
        list<Card*> deck;

};

#endif // DECK_H
