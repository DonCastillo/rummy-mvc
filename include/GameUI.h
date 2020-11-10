#ifndef GAMEUI_H_INCLUDED
#define GAMEUI_H_INCLUDED

#include <list>
#include <vector>
#include <string>
#include "Card.h"
#include "Player.h"
#include "Deck.h"

class GameUI {
 public:
    GameUI() {}
    virtual ~GameUI() {}

    virtual unsigned int requestCard(std::list<Card*>* hand) = 0;
    virtual void playFailed() = 0;
    virtual void playSucceeded() = 0;
    virtual unsigned int choosePlayer(unsigned int playerNum,
                                      unsigned int numPlayers);
    virtual void showScores(std::vector<Player*> players);
    virtual void printDeck(Deck* d);
    static unsigned int choose(std::vector<std::string> choices);
    virtual void println(std::string left, std::string right);
    virtual void print(std::string message);
    virtual void println(std::string message);
    virtual void printMapCard(Card::Suit s, std::list<Card*> right);


 protected:
    const char LINEFILL = ' ';
    const unsigned int LINEWIDTH = 35;
    const char TITLEFILL = '=';
};

#endif // GAMEUI_H_INCLUDED
