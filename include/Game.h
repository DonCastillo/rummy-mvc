#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <vector>
#include "Card.h"
#include "Deck.h"
#include "GameUI.h"
#include "Player.h"

class Game {

    public:

        virtual bool valid(Card* c) = 0;
        virtual bool isOver() = 0;
        virtual void dealCards(vector<Player*> p) = 0;
        virtual void beforeCardPlayed(unsigned int playerNum, unsigned int numPlayers) = 0;
        virtual void afterCardPlayed(Player* currentPlayer, vector<Player*> players, Card* played) = 0;

        Game(GameUI* ui, Deck* d):deck(d),ui(ui){};
        void addPlayer(Player* p);
        vector<Player*> getPlayers();
        void start();



    protected:
        vector<Player*> players;
        Deck* deck;
        GameUI* ui;
};

#endif // GAME_H_INCLUDED
