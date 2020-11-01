#ifndef RUMMYUI_H
#define RUMMYUI_H

#include <string>
#include <list>
#include "Deck.h"
#include "Player.h"
#include "Game.h"

class RummyUI : public GameUI {
 public:
    RummyUI() {}
    virtual ~RummyUI() {}

    virtual unsigned int requestCard(std::list<Card*>* hand);
    virtual void playFailed();
    virtual void playSucceeded();
 private:
};

#endif // RUMMYUI_H
