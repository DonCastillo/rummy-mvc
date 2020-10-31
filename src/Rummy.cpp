#include "Rummy.h"
#include "RummyUI.h"
#include "Card.h"
#include <vector>
#include <string>


bool Rummy::turnOver() {
    return true;
}
// deal cards
void Rummy::dealCards(std::vector<Player*> p) {
    unsigned int numOfPlayers = p.size();
    unsigned int numOfCards;

    // how many cards to give per player
    switch (numOfPlayers) {
        case 2:
            numOfCards = 10;
            break;
        case 3:
        case 4:
            numOfCards = 7;
            break;
        case 5:
        case 6:
            numOfCards = 6;
            break;
    }

    // card distribution
    for (int i = 0; i < numOfCards; ++i) {
        for (Player* x : p) {
            x->addCard(deck->getCard());
        }
    }
}

// put card to a discarded pile
void Rummy::addToDiscard(Card* c) {
    discardPile.push_back(c);
}

// draw from either the deck or discarded pile
// 0 draw from deck
// 1 draw from discarded pile
Card* Rummy::drawCard(unsigned int i) {
    Card* cardtemp;
    switch (i) {
        case 0:
            cardtemp = deck->getCard();
            break;
        case 1:
            cardtemp = discardPile.back();
            discardPile.pop_back();
            break;
    }
    return cardtemp;
}

// 0 - arrange cards by rank
// 1 - arrange cards by suit
//void Rummy::addToMatchedSets(std::vector<Card*> c, unsigned int i) {
//
//}
//
//bool Rummy::isThereMeld(Player* p) {
//    return meldRank(p, )
//}
//
//bool meldRank












