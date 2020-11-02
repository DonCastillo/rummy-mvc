#include "Rummy.h"
#include "RummyUI.h"
#include "Exceptions.h"
#include <vector>
#include <string>
#include <list>
#include <iostream>
#include <map>


/** pile of cards discarded by players */
std::list<Card*> discardPile;

/** matched sets of cards */
std::map<unsigned int, std::vector<Card*>> matchedSets;


void drawCard(Player* p, unsigned int i, Deck* d);
bool isThereMeld(Player* p);
bool meldRank(Player* p);
bool meldSuit(Player* p);


///////////////////////////////////////////////////////
void Rummy::start() {

    std::vector<std::string> drawChoices;
    drawChoices.push_back("Draw from the deck");
    drawChoices.push_back("Draw from the discarded pile");

    // check if there's a player
    if (players.empty())
        throw game_init_error("No players for game");

    // deal cards
    deck->shuffle();
    dealCards(players);

    unsigned int turn = 0;
    Player* p = players.front();

    while(!isOver()) {

        p = players.at(turn);


        //*************************print numbers
        ui->print("Deck size", std::to_string(deck->size()));
        ui->print("Discard pile size", std::to_string(discardPile.size()));
        ui->print("Matched sets size", std::to_string(matchedSets.size()));
        for(Player* p : players) {
            ui->print(p->name + "\'s hand:");
            ui->print("Hand size: ", std::to_string(p->getHand()->size()));
            std::list<Card*>* hand = p->getHand();
            std::list<Card*>::iterator card;
            for(card = hand->begin(); card != hand->end(); ++card) {
                std::cout << **card << std::endl;
            }
        }
        //*************************


        ui->print("\nCurrent player", p->name);

        // ask player where to draw
        unsigned int choice = ui->choose(drawChoices);
        // draw card
        drawCard(p, choice, deck);
        // check for melds
        bool meldExist = isThereMeld(p);
        std::cout << std::boolalpha << meldExist << std::endl;
    }
}



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


// draw from either the deck or discarded pile
// 0 draw from deck
// 1 draw from discarded pile
void drawCard(Player* p, unsigned int i, Deck* d) {
    Card* cardtemp;
    switch (i) {
        case 0:
            cardtemp = d->getCard();
            break;
        case 1:
            cardtemp = discardPile.back();
            discardPile.pop_back();
            break;
    }
    p->addCard(cardtemp);
}


bool isThereMeld(Player* p) {
    return meldRank(p) || meldSuit(p);
}



////////////////////////////////////////////////////////////////

bool meldRank(Player* p) {
    std::map<Card::Rank, std::vector<Card*>> handByRank;
    std::map<Card::Rank, std::vector<Card*>>::iterator mapIt;

    std::list<Card*>* hand = p->getHand();
    std::list<Card*>::iterator it1, it2;

    // iterate through hand
    for(it1 = hand->begin(); it1 != hand->end(); ++it1) {
        std::vector<Card*> indexes;
        for(it2 = hand->begin(); it2 != hand->end(); ++it2) {
            if((*it1)->rank == (*it2)->rank)
                indexes.push_back(*it2);
        }
        handByRank.insert(std::pair<Card::Rank, std::vector<Card*>>( (*it1)->rank, indexes ));
    }


    // iterate through the map
    for(mapIt = handByRank.begin(); mapIt != handByRank.end(); ++mapIt) {
        if(mapIt->second.size() >= 3)
            return true;
    }
    return false;
}

bool meldSuit(Player* p) {
    return false;
}

bool Rummy::turnOver() {
    return false;
}















