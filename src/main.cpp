#include "Deck.h"
#include "GoFishUI.h"
#include "GoFish.h"
#include "Rummy.h"
#include "RummyUI.h"
#include <iostream>
#include <list>
#include "Card.h"




int main() {
    Deck* d = new Deck();
    d->createStandard();
    GameUI* ui = new RummyUI();
    Game* g = new Rummy(ui, d);

    Player* trump = new Player("Trump");
    Player* biden = new Player("Biden");
    Player* pence = new Player("Pence");
    Player* harris = new Player("Harris");
    Player* pelosi = new Player("Pelosi");
    g->addPlayer(trump);
    g->addPlayer(biden);
    g->start();
}
