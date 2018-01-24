#include "Deck.h"
#include "GoFishUI.h"
#include "GoFish.h"

using namespace std;

int main()
{
    Deck* d = new Deck();
    d->createStandard();
    GameUI* ui = new GoFishUI();
    Game* g = new GoFish(ui, d);

    g->addPlayer(new Player("John"));
    g->addPlayer(new Player("Danielle"));
    g->addPlayer(new Player("Tara"));
    g->addPlayer(new Player("Erik"));
    g->addPlayer(new Player("Kira"));

    g->start();
}
