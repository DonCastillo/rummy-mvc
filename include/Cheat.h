#ifndef CHEAT_H
#define CHEAT_H

#include <Game.h>
#include <list>

using namespace std;

class Cheat : public Game
{
public:
    Cheat(GameUI* ui, Deck* d): Game(ui, d) {
        currentRank = Card::ACE;
        turnEnded = false;
    }
    virtual ~Cheat() {}

    void dealCards(vector<Player*> p);
    void beforeCardPlayed(unsigned int playerNum, unsigned int numPlayers);
    void afterCardPlayed(Player* currentPlayer, vector<Player*> players, Card* played);
    bool isOver() const;
    bool turnOver();

private:
    list<Card*> cards;
    list<Card*> pile;
    Card::Rank currentRank;
    bool turnEnded;
};

#endif // CHEAT_H
