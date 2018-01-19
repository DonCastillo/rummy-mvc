#ifndef DECK_H
#define DECK_H

using namespace std;

#include "Card.h"
#include <list>

class Deck
{
    public:

        virtual ~Deck(){}
        void shuffle();
        void addCard(Card* card);
        virtual Card* getCard();
        const unsigned int size() const;

        void createStandard();
    protected:

    private:
        list<Card*> deck;

};

#endif // DECK_H
