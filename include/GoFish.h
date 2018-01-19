#ifndef GOFISH_H
#define GOFISH_H

#include <Game.h>


class GoFish : public Game
{
    public:
        GoFish(GameUI* ui, Deck* d) : Game(ui, d){}
        virtual ~GoFish(){}

        bool valid(Card* c);
        bool isOver() const;
        void dealCards(vector<Player*> p);
        void beforeCardPlayed(unsigned int playerNum, unsigned int numPlayers);
        void afterCardPlayed(Player* currentPlayer, vector<Player*> players, Card* played);
        bool hasSet(list<Card*>* hand);

    protected:
        unsigned int playerAsked = -1;

    private:
        const unsigned int NUM_CARDS_SMALL = 7;
        const unsigned int NUM_CARDS_LARGE = 5;

};

#endif // GOFISH_H
