#ifndef RUMMY_H
#define RUMMY_H

#include <string>
#include <list>
#include <vector>
#include <map>
#include "Deck.h"
#include "Player.h"
#include "Game.h"
#include "Card.h"

class Rummy : public Game {
 public:
   /*!
      \brief    constructor
      \brief    initializes ui and deck of the derived class and base class
      \param    ui  game's user interface
                d   game's deck
   */
    Rummy(GameUI* ui, Deck* d) : Game(ui, d) {}

    /*!
       \brief desctructor
    */
    virtual ~Rummy() {}

    /*!
       \brief   deals / distributes cards to players
                2 players get 10 cards each
                3 - 4 players get 7 cards each
                5 - 6 players get 6 cards each
       \param   p players to be dealt with
    */
    void dealCards(std::vector<Player*> p);

    /*!
       \brief   main game loop
    */
    void start();
    void beforeCardPlayed(unsigned int playerNum,
                          unsigned int numPlayers) {}
    void afterCardPlayed(Player* currentPlayer, std::vector<Player*> players,
                         Card* played) {}
    bool turnOver();

 private:
};

#endif // RUMMY_H
