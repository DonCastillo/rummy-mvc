#include "Rummy.h"
#include "RummyUI.h"
#include "Deck.h"
#include "Card.h"
#include <iostream>
#include <vector>
#include <list>
#include <string>


unsigned int RummyUI::requestCard(std::list<Card*>* hand) {
    std::vector<std::string> choices;
    for (std::list<Card*>::iterator i = hand->begin(); i != hand->end(); ++i) {
        Card::Suit s = (*i)->suit;
        Card::Rank r = (*i)->rank;
        std::string card = Card::getRank(r) + ":" + Card::getSuit(s);
        choices.push_back(card);
    }
    return GameUI::choose(choices);
}

void RummyUI::playFailed() {}
void RummyUI::playSucceeded() {}
