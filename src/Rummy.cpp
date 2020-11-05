#include "Rummy.h"
#include "RummyUI.h"
#include "Exceptions.h"
#include <vector>
#include <string>
#include <list>
#include <iostream>
#include <map>
#include <algorithm>


/** pile of cards discarded by players */
std::list<Card*> discardPile;

/** matched sets of cards */
// key 0 = rank
// key 1 = suit
std::map<unsigned int, std::vector<Card*>> matchedSets;

bool sortCard(Card* a, Card* b);
void drawCard(Player* p, unsigned int i, Deck* d);
bool meldRank(std::list<Card*>* hand);
bool meldSuit(std::list<Card*>* hand);


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
        //bool meldExist = meldRank(p->getHand()) || meldSuit(p->getHand());
        //std::cout << std::boolalpha << meldExist << std::endl;
        std::list<Card*> testCards;
        testCards.push_back(new Card(Card::CLUB, Card::ACE));
        testCards.push_back(new Card(Card::CLUB, Card::TWO));
        testCards.push_back(new Card(Card::CLUB, Card::THREE));
        //testCards.push_back(new Card(Card::CLUB, Card::FOUR));

        std::cout << "*****" << std::endl;
        std::cout << std::boolalpha << meldSuit(&testCards) << std::endl;
        std::cout << "*****" << std::endl;

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

// check if 3 or 4 cards have the same rank
bool meldRank(std::list<Card*>* hand) {
    std::map<Card::Rank, std::vector<Card*>> handByRank;
    std::map<Card::Rank, std::vector<Card*>>::iterator mapIt;

    //std::list<Card*>* hand = p->getHand();
    std::list<Card*>::iterator it1, it2;

    // iterate through hand
    for(it1 = hand->begin(); it1 != hand->end(); ++it1) {
        std::vector<Card*> indexes;
        for(it2 = hand->begin(); it2 != hand->end(); ++it2) {
            // collect cards with similar rank
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

// check if 3 or more cards in the same suit are sequential
bool meldSuit(std::list<Card*>* hand) {
    std::map<Card::Suit, std::vector<Card*>> handBySuit;
    std::map<Card::Suit, std::vector<Card*>>::iterator mapIt;

    std::list<Card*>::iterator it1, it2;

    // iterate through hand
    for(it1 = hand->begin(); it1 != hand->end(); ++it1) {
        std::vector<Card*> indexes;
        for(it2 = hand->begin(); it2 != hand->end(); ++it2) {
            // collect cards with similar suit
            if((*it1)->suit == (*it2)->suit)
                indexes.push_back(*it2);
        }
        handBySuit.insert(std::pair<Card::Suit, std::vector<Card*>>( (*it1)->suit, indexes ));
     }


    // iterate through the map

    std::vector<bool> hasRun;

    for(mapIt = handBySuit.begin(); mapIt != handBySuit.end(); ++mapIt) {
        std::vector<Card*> cardTemp = mapIt->second;

        // sort cards ascendingly based on rank
        std::sort( cardTemp.begin(), cardTemp.end(), sortCard );


        // check if cards in the list are sequential
        // only consider list with at least 3 cards
        unsigned int index = -1;
        bool proceed = false;

        //std::cout << Card::getRank( cardTemp[0]->rank ) << std::endl;
        if (cardTemp.size() >= 3) {
            do {
                ++index;
                // what is next card rank
                Card::Rank a = cardTemp[index]->rank;
                a = Card::nextRank(a);

                // actual next card rank
                Card::Rank b = cardTemp[index + 1]->rank;

                bool isSequential = (a == b);
                if (isSequential)
                    proceed = true;
                else
                    proceed = false;
            } while (proceed == true && index < cardTemp.size() - 2);

            hasRun.push_back(proceed);
        }
    }

    // is there at least one sequential list
    bool hasRunFinal = false;
    for (bool b : hasRun) {
        if (b == true) {
            hasRunFinal = true;
            break;
        } else {
            hasRunFinal = false;
        }
    }



//    for(mapIt = handBySuit.begin(); mapIt != handBySuit.end(); ++mapIt) {
//        ///
//        std::cout << Card::getSuit(mapIt->first) << std::endl;
//        for(Card* c : mapIt->second) {
//            std::cout << *c << " ";
//        }
//        std::cout << std::endl;
//        ///
//    }

    return hasRunFinal;
}


bool Rummy::turnOver() {
    return false;
}

bool sortCard(Card* a, Card* b){
    return *a < *b;
}















