#include "Rummy.h"
#include "RummyUI.h"
#include "Exceptions.h"
#include <vector>
#include <string>
#include <list>
#include <iostream>
#include <map>
#include <algorithm>
#include <utility>


/** pile of cards discarded by players */
std::list<Card*> discardPile;

/** matched sets of cards */
// key 0 = rank
// key 1 = suit
std::map<unsigned int, std::vector<Card*>> matchedSets;

bool sortCard(Card* a, Card* b);
void drawCard(Player* p, unsigned int i, Deck* d);
unsigned int hasBook(std::list<Card*>* hand);
unsigned int hasRun(std::list<Card*>* hand);


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

    while (!isOver()) {
        p = players.at(turn);


        //*************************print numbers
        ui->print("Deck size", std::to_string(deck->size()));
        ui->print("Discard pile size", std::to_string(discardPile.size()));
        ui->print("Matched sets size", std::to_string(matchedSets.size()));
        for (Player* p : players) {
            ui->print(p->name + "\'s hand:");
            ui->print("Hand size: ", std::to_string(p->getHand()->size()));
            std::list<Card*>* hand = p->getHand();
            std::list<Card*>::iterator card;
            for (card = hand->begin(); card != hand->end(); ++card) {
                std::cout << **card << " ";
            }
            std::cout << "\n";
        }
        //*************************


        ui->print("\nCurrent player", p->name);

        // ask player where to draw
        unsigned int choice = ui->choose(drawChoices);
        // draw card
        drawCard(p, choice, deck);
        // check for book / run
        bool book = hasBook(p->getHand());
        bool run = hasRun(p->getHand());

        std::vector<std::string> revealChoices;
        unsigned int revealChoice = 0;

        // what to do if there's a book
        if (book) {
            revealChoices.push_back("Do nothing");
            revealChoices.push_back("Reveal book");
            ui->print("You have a book");
            revealChoice =  ui->choose(revealChoices);
            revealChoices.clear();
            switch (revealChoice) {
                case 0: break;
                case 1: // call function to reveal book
                    break;
            }
        }

        // what to do if there's a run
        if (run) {
            revealChoices.push_back("Do nothing");
            revealChoices.push_back("Reveal run");
            ui->print("You have a run");
            revealChoice = ui->choose(revealChoices);
            revealChoices.clear();
            switch (revealChoice) {
                case 0: break;
                case 1: // call function to reveal run
                    break;
            }
        }
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




// check if 3 or 4 cards have the same rank
// returns 1 if a book exist
// returns 0 if no book exist
unsigned int hasBook(std::list<Card*>* hand) {
    std::map<Card::Rank, std::vector<Card*>> handByRank;
    std::map<Card::Rank, std::vector<Card*>>::iterator mapIt;

    //std::list<Card*>* hand = p->getHand();
    std::list<Card*>::iterator it1, it2;

    // iterate through hand
    for (it1 = hand->begin(); it1 != hand->end(); ++it1) {
        std::vector<Card*> indexes;
        for (it2 = hand->begin(); it2 != hand->end(); ++it2) {
            // collect cards with similar rank
            if ((*it1)->rank == (*it2)->rank)
                indexes.push_back(*it2);
        }
        handByRank.insert(std::pair<Card::Rank,
                          std::vector<Card*>>((*it1)->rank, indexes));
    }


    // iterate through the map
    for (mapIt = handByRank.begin(); mapIt != handByRank.end(); ++mapIt) {
        if (mapIt->second.size() >= 3)
            return 1;
    }
    return 0;
}

// check if 3 or more cards in the same suit are sequential
// returns 0 if a run doesn't exist
// returns 2 if a run exists
unsigned int hasRun(std::list<Card*>* hand) {
    std::map<Card::Suit, std::vector<Card*>> handBySuit;
    std::map<Card::Suit, std::vector<Card*>>::iterator mapIt;

    std::list<Card*>::iterator it1, it2;

    // iterate through hand
    for (it1 = hand->begin(); it1 != hand->end(); ++it1) {
        std::vector<Card*> indexes;
        for (it2 = hand->begin(); it2 != hand->end(); ++it2) {
            // collect cards with similar suit
            if ((*it1)->suit == (*it2)->suit)
                indexes.push_back(*it2);
        }
        handBySuit.insert(std::pair<Card::Suit,
                          std::vector<Card*>>((*it1)->suit, indexes));
     }


    // iterate through the map
    std::vector<bool> isRunFinal;

    for (mapIt = handBySuit.begin(); mapIt != handBySuit.end(); ++mapIt) {
        std::vector<Card*> cardTemp = mapIt->second;

        // sort cards ascendingly based on rank
        std::sort(cardTemp.begin(), cardTemp.end(), sortCard);

        // check if cards in the list are sequential
        // only consider list with at least 3 cards
        bool isRun = false;

        if (cardTemp.size() >= 3) {
            unsigned int index = -1;
            unsigned int chain = 0;
            do {
                ++index;
                // what is next card rank
                Card::Rank a = cardTemp[index]->rank;
                a = Card::nextRank(a);

                // actual next card rank
                Card::Rank b = cardTemp[index + 1]->rank;

                bool isSequential = (a == b);

                if (isSequential)
                    chain++;
                else
                    chain = 0;

                if (chain >= 2)
                    isRun = true;
            } while (index < cardTemp.size() - 2);
        } else {
            isRun = false;
        }

        isRunFinal.push_back(isRun);
        mapIt->second = cardTemp;
    }

    // is there at least one sequential list
    bool tempFinal = 0;
    for (bool b : isRunFinal) {
        if (b == true) {
            tempFinal = 2;
            break;
        } else {
            tempFinal = 0;
        }
    }
//    /// print
//    for(mapIt = handBySuit.begin(); mapIt != handBySuit.end(); ++mapIt) {
//        std::cout << Card::getSuit(mapIt->first) << std::endl;
//        for(Card* c : mapIt->second) {
//            std::cout << *c << " ";
//        }
//        std::cout << std::endl;
//    }
//    /// print
    return tempFinal;
}


bool Rummy::turnOver() {
    return false;
}

bool sortCard(Card* a, Card* b) {
    return *a < *b;
}















