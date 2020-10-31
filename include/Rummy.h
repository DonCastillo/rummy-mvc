#ifndef RUMMY_H
#define RUMMY_H

#include <string>
#include <list>
#include <vector>
#include <map>
#include "Deck.h"
#include "Player.h"
#include "Game.h"
#include "Card.h"

class Rummy : public Game {
 public:
    Rummy(GameUI* ui, Deck* d) : Game(ui, d) {}
    virtual ~Rummy() {}
    void dealCards(std::vector<Player*> p);
    void beforeCardPlayed(unsigned int playerNum,
                          unsigned int numPlayers) {}
    void afterCardPlayed(Player* currentPlayer, std::vector<Player*> players,
                         Card* played);
    bool turnOver() {}
    void addToDiscard(Card* c);
    Card* drawCard(unsigned int i);
//    void addToMatchedSets(std::vector<Card*> c, unsigned int i);
//    bool isThereMeld(Player* p);

 private:
    /** pile of cards discarded by players */
    std::list<Card*> discardPile;

    /** matched sets of cards */
    std::map<unsigned int, std::vector<Card*>> matchedSets;

    /** how many rounds to determine the winner */
    unsigned int numOfRounds;
};

#endif // RUMMY_H
