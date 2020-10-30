#ifndef RUMMY_H
#define RUMMY_H

#include <string>
#include <list>
#include "Deck.h"
#include "Player.h"
#include "Game.h"

class Rummy : public Game {
 public:
    Rummy(GameUI* ui, Deck* d) : Game(ui, d) {}
    virtual ~Rummy() {}
    void dealCards(std::vector<Player*> p);

 private:

};

#endif // RUMMY_H
