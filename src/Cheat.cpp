#include "Cheat.h"

#include <iostream>
#include <vector>
#include <list>

void Cheat::dealCards(const vector<Player*> p) {
    unsigned int playerNum = 0;
    while (deck->size() > 0) {
        //cout << "Deck Size: " << deck->size() << endl;
        Player* p = players.at(playerNum);
        p->addCard(deck->getCard());
        playerNum = ++playerNum % players.size();
    }
}

void Cheat::beforeCardPlayed(unsigned int playerNum, unsigned int numPlayers) {
    turnEnded = false;
}

void Cheat::afterCardPlayed(Player* currentPlayer, vector<Player*> players,
                            Card* played) {
    if (valid(played)) {
        cards.push_back(played);
    } else {
        turnEnded = true;
        // Remove cards from players hand
        for (list<Card*>::iterator card = cards.begin();
                card != cards.end(); ++card) {
            currentPlayer->getHand()->remove(*card);
        }

        // callCheat holds the player number of who called "Cheat"
        unsigned int callCheat = ui->choosePlayer(-1, -1);
        if (callCheat < players.size()) {
            bool caught = false;
            for (list<Card*>::iterator card = cards.begin();
                    card != cards.end(); ++card) {
                if ((*card)->rank != currentRank) {
                    caught = true;
                }
            }

            // Move cards to pile
            pile.insert(pile.begin(), cards.begin(), cards.end());
            cards.clear();

            if (caught) {
                // Move pile to player's hand
                currentPlayer->getHand()->
                insert(currentPlayer->getHand()->begin(),
                       pile.begin(), pile.end());

            } else {
                players[callCheat]->getHand()->
                    insert(players[callCheat]->getHand()->begin(),
                    pile.begin(),
                    pile.end());
            }
            pile.clear();
        } else {
            // Move cards to pile
            pile.insert(pile.begin(), cards.begin(), cards.end());
            cards.clear();
        }

        // Move to next rank
        currentRank = Card::nextRank(currentRank);
    }
}

bool Cheat::isOver() const {
    for (Player* p : players)
        if (p->getHand()->empty()) {
            p->addPoints(1);
            return true;
        }
    return false;
}

bool Cheat::turnOver() {
    return turnEnded;
}
