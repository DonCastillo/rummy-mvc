#ifndef GOFISHUI_H
#define GOFISHUI_H

#include "GameUI.h"
#include "Card.h"

class GoFishUI : public GameUI
{
public:
    GoFishUI() {}
    ~GoFishUI() {}

    unsigned int requestCard(list<Card*>* hand);
    void playFailed();
    void playSucceeded();
};

#endif // GOFISHUI_H
