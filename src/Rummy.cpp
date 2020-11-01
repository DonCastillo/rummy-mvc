#include "Rummy.h"
#include <vector>
#include <string>
#include <list>
#include <iostream>



void createDiscardPile(Deck* d, std::list<Card*> dp);
void addToDiscard(Card* c);
Deck* getDeck();
std::list<Card*> getDiscardPile();
void drawCard(Player* p, unsigned int i);


/////////////////////////////////////////////////////// deal cards
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

    // create a discarded pile
    if (deck->size() > 0) {
        discardPile.push_back(deck->getCard());
    }
}

////////////////////////////////////////////////////////////////

//// current player index, all players in the game
//void Rummy::beforeCardPlayed(unsigned int playerNum,
//                             unsigned int numPlayers) {
//
//}






bool Rummy::turnOver() {
    std::cout << discardPile.size() << std::endl;
    return true;
}

// put card to a discarded pile
//void addToDiscard(Card* c) {
//    discardPile.push_back(c);
//}
//
//// get deck
//Deck* getDeck() {
//    return deck;
//}

//std::list<Card*> getDiscardPile() {
//    return discardPile;
//}

// draw from either the deck or discarded pile
// 0 draw from deck
// 1 draw from discarded pile
void Rummy::drawCard(Player* p, unsigned int i) {
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
    p->addCard(cardtemp);
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


void Rummy::start() {


}














