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
std::map<std::string, std::list<Card*>> matchedSets;
void insertToMatchedSets(char c, std::list<Card*> cardsSet);
void layoff(Player* player, GameUI* pUI);
bool sortCard(Card* a, Card* b);
void drawCard(Player* p, unsigned int i, Deck* d);
bool insertToBook(Player* player, Card* card);
bool insertToRun(Player* player, Card* card);
unsigned int hasBook(bool reveal, Player* player);
unsigned int hasRun(bool reveal, Player* player);


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
        ui->println("Deck size", std::to_string(deck->size()));
        ui->println("Discard pile size", std::to_string(discardPile.size()));
        ui->println("Matched sets size", std::to_string(matchedSets.size()));
        for (Player* p : players) {
            ui->println(p->name + "\'s hand: " + "[" +
                        std::to_string(p->getHand()->size()) + "]");
            std::list<Card*>* hand = p->getHand();
            std::list<Card*>::iterator card;
            for (card = hand->begin(); card != hand->end(); ++card) {
                std::cout << **card << "  ";
            }
            std::cout << "\n";
        }
        //*************************

        //*************************print maps
        ui->println("Matched set");
        std::map<std::string, std::list<Card*>>::iterator mapIt;
        for (mapIt = matchedSets.begin(); mapIt != matchedSets.end(); ++mapIt) {
            ui->print(mapIt->first);
            ui->print(" => ");
            for (Card* c : mapIt->second) {
                ui->print(Card::getRank(c->rank));
                ui->print(":");
                ui->print(Card::getSuit(c->suit));
                ui->print("  ");
            }
            ui->println("");
        }


        //*************************************


        ui->println("\nCurrent player", p->name);

        // ask player where to draw
        unsigned int choice = ui->choose(drawChoices);
        // draw card
        drawCard(p, choice, deck);
        // check for book / run

        std::vector<std::string> revealChoices;
        unsigned int revealChoice = 0;

        // what to do if there's a book
        if (hasBook(false, p)) {
            revealChoices.push_back("Do nothing");
            revealChoices.push_back("Reveal book");
            ui->println("You have a book");
            revealChoice =  ui->choose(revealChoices);
            revealChoices.clear();
            switch (revealChoice) {
                case 0: break;
                case 1: hasBook(true, p);
                    break;
            }
        }

        // what to do if there's a run
        if (hasRun(false, p)) {
            revealChoices.push_back("Do nothing");
            revealChoices.push_back("Reveal run");
            ui->println("You have a run");
            revealChoice = ui->choose(revealChoices);
            revealChoices.clear();
            switch (revealChoice) {
                case 0: break;
                case 1: hasRun(true, p);// call function to reveal run
                    break;
            }
        }

        // ask player to choose which card to reveal
        layoff(p, ui);
    }
}


void layoff(Player* player, GameUI* pUI) {
    if (matchedSets.size() > 0) {
        std::vector<std::string> layoffChoices;
        layoffChoices.push_back("Yes");
        layoffChoices.push_back("No");
        pUI->println("Do you want to layoff card?: ");
        unsigned int choice = pUI->choose(layoffChoices);
        if (choice != 0)
            return;

        std::cout << "Don Castillo" << std::endl;

        // if player has a card in hand
        if (player->getHand()->size() > 0) {
            // get card index
            unsigned int index = pUI->requestCard(player->getHand());

            // get the actual card
            Card* pickedCard = player->getCard(index);
            Card::Rank r = pickedCard->rank;
            Card::Suit s = pickedCard->suit;

            // print picked card
            pUI->print("Picked Card: ");
            pUI->println(Card::getRank(r) + ":" + Card::getSuit(s));

            // collect row of cards in map and print it as choices
            std::map<std::string, std::list<Card*>>::iterator mapIt;
            std::vector<std::string> choices;

            for (mapIt = matchedSets.begin();
                 mapIt != matchedSets.end(); ++mapIt) {
                std::string choiceRow = "";
                for (Card* c : mapIt->second) {
                    choiceRow.append(Card::getRank(c->rank));
                    choiceRow.append(":");
                    choiceRow.append(Card::getSuit(c->suit));
                    choiceRow.append("  ");
                }
                choices.push_back(choiceRow);
            }
            choices.push_back("Exit");


            ///-------------------------
            bool isSuccessful = true;
            do {
                // get index of selected map row
                unsigned int exit = choices.size() - 1;
                unsigned int mapIndex = pUI->choose(choices);

                // access actual row of map based on chosen mapIndex
                unsigned int counter = 0;
                std::string key = "";
                char mode;

                // exit
                if (mapIndex == exit)
                    break;

                // get the first char of the map key to know if it's
                // a suit or rank based insertion
                for (mapIt = matchedSets.begin();
                     mapIt != matchedSets.end(); ++mapIt) {
                    if (mapIndex == counter)
                        key = mapIt->first;
                    ++counter;
                }

                // get mode

                mode = key[0];
                switch (mode) {
                    case 'r':
                        isSuccessful = insertToBook(player, pickedCard);
                        std::cout << std::boolalpha
                                  << isSuccessful << std::endl;
                        break;
                    case 's':
                        isSuccessful = insertToRun(player, pickedCard);
                        break;
                }
            } while (!isSuccessful);
            ///-------------------------
        }
    }
}


bool insertToBook(Player* player, Card* card) {
    bool success = false;
    std::map<std::string, std::list<Card*>>::iterator mapIt;

    for (mapIt = matchedSets.begin(); mapIt != matchedSets.end(); ++mapIt) {
        std::string key        = mapIt->first;
        std::list<Card*> value = mapIt->second;

        // rank
        if (key[0] == 'r') {
            if (card->rank == value.front()->rank) {
                (mapIt->second).push_back(card);
                player->removeCard(card);
                success = true;
                break;
            }
        }
    }

    return success;
}


bool insertToRun(Player* player, Card* card) {}

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
unsigned int hasBook(bool reveal, Player* player) {
    std::list<Card*>* hand = player->getHand();
    std::map<Card::Rank, std::vector<Card*>> handByRank;
    std::map<Card::Rank, std::vector<Card*>>::iterator mapIt;

    //std::list<Card*>* hand = p->getHand();
    std::list<Card*>::iterator it1, it2;

    // iterate through hand
    for (it1 = hand->begin(); it1 != hand->end(); ++it1) {
        std::vector<Card*> indexes;
        unsigned int counter = 0;
        for (it2 = hand->begin(); it2 != hand->end(); ++it2) {
            // collect cards with similar rank
            if ((*it1)->rank == (*it2)->rank)
                indexes.push_back(*it2);
            ++counter;
        }
        handByRank.insert(std::pair<Card::Rank,
                          std::vector<Card*>>((*it1)->rank, indexes));
    }



    /// print before deletion ////////////////
    std::cout << "\n" << "Possible Book" << std::endl;
    for (mapIt = handByRank.begin(); mapIt != handByRank.end(); ++mapIt) {
        std::cout << Card::getRank(mapIt->first) << " => ";
        for (Card* c : mapIt->second)
            std::cout << *c << "  ";
        std::cout << "\n";
    }
    std::cout << std::endl;
    /// print ////////////////////////////////




    // iterate through the map
    for (mapIt = handByRank.begin(); mapIt != handByRank.end(); ++mapIt) {
        if (mapIt->second.size() >= 3) {
            if (reveal) {
                std::list<Card*> cardsSet;

                for (Card* c : mapIt->second) {
                    cardsSet.push_back(c);
                    player->removeCard(c);
                }
                insertToMatchedSets('r', cardsSet);
                return 1;
            } else {
                return 1;
            }
        }
    }



//    std::cout << "%%%%%%%%" << std::endl;
//    /// print before deletion ////////////////
//    for (mapIt = handByRank.begin(); mapIt != handByRank.end(); ++mapIt) {
//        std::cout << Card::getRank(mapIt->first) << " => ";
//        for (Card* c : mapIt->second)
//            std::cout << *c << "  ";
//        std::cout << "\n";
//    }
//    std::cout << "%%%%%%%%" << std::endl;
//    /// print ////////////////////////////////
    return 0;
}


// check if 3 or more cards in the same suit are sequential
// returns 0 if a run doesn't exist
// returns 2 if a run exists
unsigned int hasRun(bool reveal, Player* player) {
    std::list<Card*>* hand = player->getHand();
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






     /// print before deletion ////////////////
    std::cout << "\n" << "Possible Run" << std::endl;
    for (mapIt = handBySuit.begin(); mapIt != handBySuit.end(); ++mapIt) {
        std::cout << Card::getSuit(mapIt->first) << " => ";
        for (Card* c : mapIt->second)
            std::cout << *c << "  ";
        std::cout << "\n";
    }
    std::cout << std::endl;
    /// print ////////////////////////////////


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
        ///------------------------------------------------------------------------
            Card::Suit key = mapIt->first; // get the handBySuit key
            std::list<Card*> value;
            int index = -1;
            unsigned int chain = 0;

            do {
                ++index;
                // what is next card rank
                Card::Rank a = cardTemp[index]->rank;
                a = Card::nextRank(a);

                // actual next card rank
                Card::Rank b = cardTemp[index + 1]->rank;

                bool isSequential = (a == b);

                if (isSequential) {
                   chain++;
                   value.push_back(cardTemp[index]);
                   value.push_back(cardTemp[index + 1]);
                   value.unique();
                } else {
                    if (chain >= 2)
                        break;
                    if (value.size() < 3)
                        value.clear();
                    chain = 0;
                }

                if (chain >= 2)
                    isRun = true;
            } while (index < cardTemp.size() - 2);

            if (reveal) {
                for (Card* c : value) {
                    player->removeCard(c);
                }
                //value.clear();
                insertToMatchedSets('s', value);
                // remove card
            }
        ///------------------------------------------------------------------------
        } else {
            isRun = false;
        }
        isRunFinal.push_back(isRun);
        //mapIt->second = cardTemp;
    }


    // is there at least one sequential list
    unsigned int tempFinal = 0;
    for (bool b : isRunFinal) {
        if (b == true) {
            tempFinal = 2;
            break;
        } else {
            tempFinal = 0;
        }
    }


    return tempFinal;
}


bool Rummy::turnOver() {
    return false;
}

bool sortCard(Card* a, Card* b) {
    return *a < *b;
}

// [r/s]-[#]
void insertToMatchedSets(char c, std::list<Card*> cardsSet) {
    unsigned int num = matchedSets.size();
    std::string key = "";
    key.push_back(c);
    key.append("-");
    key.append(std::to_string(num));
    matchedSets.insert(std::pair<std::string, std::list<Card*>>(key, cardsSet));
    std::cout << "^^^^^^^^^^^^^^^^^^^^^^^^" << std::endl;
    std::cout << key << std::endl;
    std::cout << "^^^^^^^^^^^^^^^^^^^^^^^^" << std::endl;
}















