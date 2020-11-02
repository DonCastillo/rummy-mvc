#include "Rummy.h"
#include "RummyUI.h"
#include "Exceptions.h"
#include <vector>
#include <string>
#include <list>
#include <iostream>


/** pile of cards discarded by players */
std::list<Card*> discardPile;

/** matched sets of cards */
std::map<unsigned int, std::vector<Card*>> matchedSets;

void createDiscardPile(Deck* d, std::list<Card*> dp);
void addToDiscard(Card* c);
Deck* getDeck();
std::list<Card*> getDiscardPile();
void drawCard(Player* p, unsigned int i, Deck* d);


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

    //*************************print numbers
    ui->print("Deck size", std::to_string(deck->size()));
    ui->print("asa", "asas");
    ui->print("Discard pile size", std::to_string(discardPile.size()));
    ui->print("Matched sets", std::to_string(matchedSets.size()));
    for(Player* p : players)
        ui->print(p->name, std::to_string(p->getHand()->size()));
    //*************************

    unsigned int turn = 0;
    Player* p = players.front();

    while(!isOver()) {
        p = players.at(turn);
        // ask player where to draw
        unsigned int choice = ui->choose(drawChoices);
        // draw card
        drawCard(p, choice, deck);

        //*************************print numbers
        ui->print("Deck size", std::to_string(deck->size()));
        ui->print("Discard pile size", std::to_string(discardPile.size()));
        ui->print("Matched sets", std::to_string(matchedSets.size()));
        for(Player* p : players)
            ui->print(p->name, std::to_string(p->getHand()->size()));
        //*************************

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

















