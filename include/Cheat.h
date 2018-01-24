#ifndef CHEAT_H
#define CHEAT_H

#include <Game.h>

class Cheat : public Game
{
public:
    Cheat(GameUI* ui, Deck* d): Game(ui, d) {}
    virtual ~Cheat() {}

    void dealCards(vector<Player*> p);
    void beforeCardPlayed(unsigned int playerNum, unsigned int numPlayers);
    void afterCardPlayed(Player* currentPlayer, vector<Player*> players, Card* played);;

protected:

private:
};

#endif // CHEAT_H
