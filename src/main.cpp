#include "Deck.h"
#include "GoFishUI.h"
#include "GoFish.h"
#include "Rummy.h"
#include "RummyUI.h"
#include "GameUI.h"
#include <iostream>
#include <vector>
#include "Card.h"


int main() {
    Deck* d = new Deck();
    d->createStandard();

    std::cout << "What game to play?\n";
    std::vector<std::string> choices;
    choices.push_back("Go Fish");
    choices.push_back("Rummy");
    unsigned int index = GameUI::choose(choices);
    GameUI* ui;
    Game* g;

    // which game to play
    switch (index) {
        case 0:
            ui = new GoFishUI();
            g = new GoFish(ui, d);
            break;
        case 1:
            ui = new RummyUI();
            g = new Rummy(ui, d);
            break;
    }

    // add players
    Player* michael = new Player("Michael");
    Player* dwight = new Player("Dwight");
    Player* jim = new Player("Jim");
    Player* pam = new Player("Pam");
    g->addPlayer(michael);
    g->addPlayer(dwight);
    g->addPlayer(jim);
    g->addPlayer(pam);
    g->start();

    delete michael;
    delete dwight;
    delete jim;
    delete pam;
    delete ui;
    delete g;
}
