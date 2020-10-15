#ifndef GOFISHUI_H
#define GOFISHUI_H

#include "GameUI.h"
#include "Card.h"
#include <list>

class GoFishUI : public GameUI {
 public:
    GoFishUI() {}
    ~GoFishUI() {}

    unsigned int requestCard(std::list<Card*>* hand);
    void playFailed();
    void playSucceeded();
};

#endif // GOFISHUI_H
