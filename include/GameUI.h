#ifndef GAMEUI_H_INCLUDED
#define GAMEUI_H_INCLUDED

#include <list>
#include <vector>
#include "Card.h"
#include "Player.h"

using namespace std;

class GameUI {

  public:
    GameUI() {}
    virtual ~GameUI() {}

    virtual unsigned int requestCard(list<Card*>* hand) = 0;
    virtual void playFailed() = 0;
    virtual void playSucceeded() = 0;
    virtual unsigned int choosePlayer(unsigned int playerNum,
                                      unsigned int numPlayers);
    virtual void showScores(vector<Player*> players);
};

#endif // GAMEUI_H_INCLUDED
