#include "Deck.h"
#include "GoFishUI.h"
#include "GoFish.h"
#include "Rummy.h"
#include "RummyUI.h"
#include <iostream>
#include <list>
#include "Card.h"




int main() {
//    Deck* d = new Deck();
//    d->createStandard();
//    GameUI* ui = new GoFishUI();
//    Game* g = new GoFish(ui, d);
//
//    g->addPlayer(new Player("John"));
//    g->addPlayer(new Player("Danielle"));
//    g->addPlayer(new Player("Tara"));
//    g->addPlayer(new Player("Erik"));
//    g->addPlayer(new Player("Kira"));
//
////    g->start();
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
//    std::vector<Card*> num;
//    num.push_back(new Card(Card::CLUB, Card::KING));
//    num.push_back(new Card(Card::CLUB, Card::JACK));
//    num.push_back(new Card(Card::CLUB, Card::TWO));
//    num.push_back(new Card(Card::CLUB, Card::QUEEN));
//
////    num.sort();
//    std::sort(num.begin(), num.end(), don);
////    //std::cout << std::boolalpha << (*num[2] == *(new Card(Card::CLUB, Card::TWO)));
////    //std::cout << *num[0];
//////    num.sort();
//    for(Card* x : num)
//        std::cout << *x << std::endl;
//
////    for(Card* x : num)
////        std::cout << *x << std::endl;
}
