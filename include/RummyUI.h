#ifndef RUMMYUI_H
#define RUMMYUI_H

#include <string>
#include <list>
#include "Deck.h"
#include "Player.h"
#include "Game.h"
#include "GameUI.h"

class RummyUI : public GameUI {
 public:
    RummyUI() {}
    virtual ~RummyUI() {}

    unsigned int requestCard(std::list<Card*>* hand);
    void playFailed();
    void playSucceeded();

    //void printDeck();
 private:
};

#endif // RUMMYUI_H
