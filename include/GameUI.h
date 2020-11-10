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
    static unsigned int choose(std::vector<std::string> choices);
    static void println(std::string left, std::string right);
    static void print(std::string message);
    static void println(std::string message);
};

#endif // GAMEUI_H_INCLUDED
