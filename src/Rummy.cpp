#include "Rummy.h"
#include "RummyUI.h"
#include <vector>
#include <string>


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
    for(int i = 0; i < numOfCards; ++i) {
        for (Player* x : p) {
            x->addCard(deck->getCard());
        }
    }
}
