#include "Rummy.h"
#include "RummyUI.h"
#include "GameUI.h"
#include "Exceptions.h"
#include <vector>
#include <string>
#include <list>
#include <map>
#include <algorithm>
#include <utility>


/** pile of cards discarded by players */
std::list<Card*> discardPile;

/** matched sets of cards */
// map 0 = <r/s>-<id> => run/book
std::map<std::string, std::list<Card*>> matchedSets;
void insertToMatchedSets(char c, std::list<Card*> cardsSet);
void layoff(Player* player, GameUI* pUI);
void discard(Player* player, GameUI* pUI);
bool sortCard(Card* a, Card* b);
bool drawCard(Player* p, unsigned int i, Deck* d);
bool insertToBook(Player* player, Card* card);
bool insertToRun(Player* player, Card* card);
unsigned int hasBook(bool reveal, Player* player);
unsigned int hasRun(bool reveal, Player* player);
void displayStats(std::vector<Player*> players, Deck* deck);
void displayMatchedSets();
void replenishDeck(Deck* deck);
void determineWinner(std::vector<Player*> players);


void Rummy::start() {
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
        displayStats(players, deck);
        displayMatchedSets();
        // display current player
        GameUI::println("\nCurrent player", p->name);

        // ask player where to draw
        bool successDraw = true;
        do {
            std::vector<std::string> drawChoices;
            drawChoices.push_back("Draw from the deck");
            drawChoices.push_back("Draw from the discarded pile");
            unsigned int choice = GameUI::choose(drawChoices);
            drawChoices.clear();
            if (deck->size() > 0 && discardPile.size() > 0)
                successDraw = drawCard(p, choice, deck);
        } while (!successDraw);


        // check for book / run
        std::vector<std::string> revealChoices;
        int revealBook = 0, revealRun = 0;

        // what to do if there's a book
        if (hasBook(false, p)) {
            revealChoices.push_back("Do nothing");
            revealChoices.push_back("Reveal book");
            GameUI::println("You have a book");
            revealBook =  GameUI::choose(revealChoices);
            revealChoices.clear();
            switch (revealBook) {
                case 0: break;
                case 1: hasBook(true, p);
                    break;
            }
        } else {
            GameUI::println("No book");
        }

        // what to do if there's a run
        if (hasRun(false, p)) {
            revealChoices.push_back("Do nothing");
            revealChoices.push_back("Reveal run");
            GameUI::println("You have a run");
            revealRun = GameUI::choose(revealChoices);
            revealChoices.clear();
            switch (revealRun) {
                case 0: break;
                case 1: hasRun(true, p);
                    break;
            }
        } else {
            GameUI::println("No Run");
            GameUI::println("");
        }

        // ask player to choose which card to reveal
        layoff(p, ui);

        // discard a card
        if (p->getHand()->size() > 0)
            discard(p, ui);

        // next player
        turn = ++turn % players.size();
    }

    determineWinner(players);
}

/*!
   \brief   display who the winner is depending
            on who gets an empty hand first
   \param   players   list of players in the game
*/
void determineWinner(std::vector<Player*> players) {
    for (Player* p : players) {
        if (p->getHand()->size() == 0)
            GameUI::println("Congrats, " + p->name);
    }
}

/*!
   \brief   displays the current matchedset
*/
void displayMatchedSets() {
    // print matched sets
    if (matchedSets.size() > 0) {
        GameUI::println("\nMatched set");
        std::map<std::string, std::list<Card*>>::iterator mapIt;
        for (mapIt = matchedSets.begin(); mapIt != matchedSets.end(); ++mapIt) {
            GameUI::print(mapIt->first);
            GameUI::print(" => ");
            for (Card* c : mapIt->second) {
                GameUI::print(Card::getRank(c->rank));
                GameUI::print(":");
                GameUI::print(Card::getSuit(c->suit));
                GameUI::print("  ");
            }
            GameUI::println("\n");
        }
    }
}


/*!
   \brief   displays current size of deck, discarded pile, and player's hands
   \param   deck      deck
            players   lists of players in the game
*/
void displayStats(std::vector<Player*> players, Deck* deck) {
    // print numbers
    GameUI::println("");
    GameUI::println("Deck size", std::to_string(deck->size()));
    GameUI::println("Discard pile size", std::to_string(discardPile.size()));

    for (Player* p : players) {
        GameUI::print(p->name + "\'s hand: " + "[" +
                    std::to_string(p->getHand()->size()) + "] ");
        std::list<Card*>* hand = p->getHand();
        std::list<Card*>::iterator card;
        for (card = hand->begin(); card != hand->end(); ++card) {
            //std::cout << **card << "  ";
            GameUI::print(Card::getRank((*card)->rank));
            GameUI::print(":");
            GameUI::print(Card::getSuit((*card)->suit));
            GameUI::print("  ");
        }
        GameUI::println("");
    }
}


/*!
   \brief   lets the player discards a card from his hand
   \param   player    player discarding the card
*/
void discard(Player* player, GameUI* pUI) {
    GameUI::println("Discard a card");
    // get card index
    unsigned int index = pUI->requestCard(player->getHand());

    // get the actual card
    Card* pickedCard = player->getCard(index);

    // add to discard pile
    discardPile.push_back(pickedCard);

    // remove card from player's hand
    player->removeCard(pickedCard);
}


/*!
   \brief   lays off a card from the player's hand into a book or run
            in the matchedSet
   \param   player    player inserting the card
*/
void layoff(Player* player, GameUI* pUI) {
    if (matchedSets.size() > 0) {
        // if player has a card in hand
        if (player->getHand()->size() > 0) {
            unsigned int choice = 0;
            do {
                std::vector<std::string> layoffChoices;
                layoffChoices.push_back("Yes");
                layoffChoices.push_back("No");
                GameUI::println("Do you want to layoff card?: ");
                choice = GameUI::choose(layoffChoices);
                GameUI::println("");
                if (choice != 0)
                    break;

                // print map
                displayMatchedSets();
                // get card index
                GameUI::println("\nWhich card to insert to the matched sets?");
                unsigned int index = pUI->requestCard(player->getHand());

                // get the actual card
                Card* pickedCard = player->getCard(index);
                Card::Rank r = pickedCard->rank;
                Card::Suit s = pickedCard->suit;

                // print picked card
                GameUI::print("Picked Card: ");
                GameUI::println(Card::getRank(r) + ":" + Card::getSuit(s));

                // collect row of cards in map and print it as choices
                std::map<std::string, std::list<Card*>>::iterator mapIt;
                std::vector<std::string> choices;

                GameUI::println("Which set to insert the picked card?");
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

                bool isSuccessful = true;
                do {
                    // get index of selected map row
                    unsigned int exit = choices.size() - 1;
                    unsigned int mapIndex = GameUI::choose(choices);

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
                            break;
                        case 's':
                            isSuccessful = insertToRun(player, pickedCard);
                            break;
                    }
                } while (!isSuccessful);
            } while (choice == 0);
        }
    }
}

/*!
   \brief   inserts a card into the run set in the matchedSet and removes
            that card from the player's hand
   \param   player    player inserting the card
            card      card to be inserted
   \return  return true if insertion is successful, otherwise false
*/
bool insertToRun(Player* player, Card* card) {
    bool success = false;
    std::map<std::string, std::list<Card*>>::iterator mapIt;

    for (mapIt = matchedSets.begin(); mapIt != matchedSets.end(); ++mapIt) {
        std::string key        = mapIt->first;
        std::list<Card*> value = mapIt->second;

        // suit
        if (key[0] == 's') {
            // check if card to be inserted has the
            // same suit as the cards in the map
            if (card->suit == value.front()->suit) {
                // if card is KING : x
                bool proceed = false;

                switch (card->rank) {
                    case Card::KING:
                        proceed = (value.back()->rank == Card::QUEEN) ?
                                                        true : false;
                        break;
                    case Card::ACE:
                        proceed = (value.front()->rank == Card::TWO) ?
                                                        true : false;
                        break;
                    default:
                        Card::Rank frontRank = value.front()->rank;
                        Card::Rank backRank = value.back()->rank;
                        bool okayFront = false, okayBack = false;
                        okayFront = Card::nextRank(card->rank) ==
                                        frontRank ? true : false;
                        okayBack = Card::prevRank(card->rank) ==
                                        backRank ? true : false;
                        proceed = okayFront || okayBack;
                        break;
                }

                if (proceed) {
                    value.push_back(card);
                    value.sort(sortCard);
                    mapIt->second = value;
                    player->removeCard(card);
                    success = true;
                } else {
                    success = false;
                }
            }
        }
    }
    return success;
}


/*!
   \brief   inserts a card into the book set in the matchedSet and removes
            that card from the player's hand
   \param   player    player inserting the card
            card      card to be inserted
   \return  return true if insertion is successful, otherwise false
*/
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



/*!
   \brief   draw from either the deck of discarded pile
   \param   p   player to draw
            i   where to draw:
                0 = draw from the deck
                1 = draw from the discarded pile
            d   deck
   \return  returns true if drawing was successful, false if not
*/
bool drawCard(Player* p, unsigned int i, Deck* d) {
    Card* cardtemp;
    bool success = false;
    switch (i) {
        case 0:
            do {
                cardtemp = d->getCard();
                if (cardtemp == nullptr && discardPile.size() > 1) {
                    success = false;
                    replenishDeck(d);
                    continue;
                } else if (cardtemp == nullptr && discardPile.size() == 1) {
                    success = false;
                    break;
                } else {
                    success = true;
                    break;
                }
            } while (true);
            break;
        case 1:
            if (discardPile.size() > 0) {
                cardtemp = discardPile.back();
                discardPile.pop_back();
                success = true;
            } else {
                success = false;
            }
            break;
    }
    if (success)
        p->addCard(cardtemp);

    return success;
}



/*!
   \brief   refill the deck from the discard pile of cards
   \param   deck    deck to be refilled
*/
void replenishDeck(Deck* deck) {
    Card* cardToRetain = discardPile.front();
    discardPile.pop_front();
    for (Card* c : discardPile)
        deck->addCard(c);
    discardPile.push_back(cardToRetain);
}


/*!
   \brief   check if 3 or 4 cards have the same rank in the player's hand
   \param   reveal    true = removes cards that belong in a book and
                             put them into the matchedSets
                      false = does not remove cards
   \return  0  means book does not exist
            1  means book exist
*/
unsigned int hasBook(bool reveal, Player* player) {
    std::list<Card*>* hand = player->getHand();
    std::map<Card::Rank, std::vector<Card*>> handByRank;
    std::map<Card::Rank, std::vector<Card*>>::iterator mapIt;

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

    // display possible book
    if (!reveal) {
        GameUI::println("\nPossible Book");
        for (mapIt = handByRank.begin(); mapIt != handByRank.end(); ++mapIt) {
            GameUI::print(Card::getRank(mapIt->first) + " => ");
            for (Card* c : mapIt->second) {
                GameUI::print(Card::getRank((*c).rank));
                GameUI::print(":");
                GameUI::print(Card::getSuit((*c).suit));
                GameUI::print(" ");
            }
            GameUI::println("");
        }
        GameUI::println("");
    }


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
    return 0;
}


/*!
   \brief   check if 3 or more cards in the same suit are sequential
            in the player's hand
   \param   reveal    true = removes cards that belong in a run
                             and put them into the matchedSets
                      false = does not remove cards
   \return  0  means run does not exist
            2  means run exist
*/
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

    // display possible run
    if (!reveal) {
        GameUI::println("\nPossible Run");
        for (mapIt = handBySuit.begin(); mapIt != handBySuit.end(); ++mapIt) {
            GameUI::print(Card::getSuit(mapIt->first) + " => ");
            for (Card* c : mapIt->second) {
                GameUI::print(Card::getRank((*c).rank));
                GameUI::print(":");
                GameUI::print(Card::getSuit((*c).suit));
                GameUI::print(" ");
            }
            GameUI::println("");
        }
        GameUI::println("");
    }


    std::vector<bool> isRunFinal;

    for (mapIt = handBySuit.begin(); mapIt != handBySuit.end(); ++mapIt) {
        std::vector<Card*> cardTemp = mapIt->second;

        // sort cards ascendingly based on rank
        std::sort(cardTemp.begin(), cardTemp.end(), sortCard);

        // check if cards in the list are sequential
        // only consider list with at least 3 cards
        bool isRun = false;

        if (cardTemp.size() >= 3) {
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

            if (reveal && value.size() >= 3) {
                for (Card* c : value) {
                    player->removeCard(c);
                }
                insertToMatchedSets('s', value);
            }
        } else {
            isRun = false;
        }
        isRunFinal.push_back(isRun);
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

/*!
   \brief   compares cards if first card less than the second card
   \param   a   first card
            b   second card
   \return  true if first card is less than the second card, otherwise false
*/
bool sortCard(Card* a, Card* b) {
    return *a < *b;
}

/*!
   \brief   insert a set of cards to the matched set map
   \param   c   key of the map based on the type of meld or set
                r = sets of cards to be inserted are books
                    (same rank)
                s = sets of cards to be inserted are run
                    (same suit and sequential)
            cardsSet  set of cards to be inserted
*/
void insertToMatchedSets(char c, std::list<Card*> cardsSet) {
    unsigned int num = matchedSets.size();
    std::string key = "";
    key.push_back(c);
    key.append("-");
    key.append(std::to_string(num));
    matchedSets.insert(std::pair<std::string, std::list<Card*>>(key, cardsSet));
}
