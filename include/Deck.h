#ifndef DECK_H
#define DECK_H

using namespace std;

#include "Card.h"
#include <list>

class Deck
{
    public:

        virtual ~Deck(){}
        virtual void shuffle();
        virtual void addCard(Card* card);
        virtual Card* getCard();
        virtual unsigned int size();

        void createStandard();
    protected:

    private:
        list<Card*> deck;

};

#endif // DECK_H
