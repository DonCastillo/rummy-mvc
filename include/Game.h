#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <vector>
#include "Card.h"
#include "Deck.h"
#include "GameUI.h"
#include "Player.h"

class Game {
 public:
    virtual void dealCards(std::vector<Player*> p) = 0;
    virtual void beforeCardPlayed(unsigned int playerNum,
                                  unsigned int numPlayers) = 0;
    virtual void afterCardPlayed(Player* currentPlayer, std::vector<Player*> players,
                                 Card* played) = 0;
    virtual bool turnOver() = 0;

    Game(GameUI* ui, Deck* d):deck(d), ui(ui) {}
    virtual ~Game() {}    
    virtual bool isOver() const;

    void addPlayer(Player* p);
    std::vector<Player*> getPlayers();
    void start();

 protected:
    std::vector<Player*> players;
    Deck* deck;
    GameUI* ui;
};

#endif // GAME_H_INCLUDED
