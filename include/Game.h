#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <vector>
#include "Card.h"
#include "Deck.h"
#include "GameUI.h"
#include "Player.h"

class Game {

    public:

        virtual void play() = 0;
        virtual bool validate(Card* c) = 0;
        virtual bool isOver() = 0;

        Game(GameUI* ui, Deck* d):deck(d),ui(ui){};
        void addPlayer(Player* p);
        void start();



    protected:
        vector<Player*> players;
        Deck* deck;
        GameUI* ui;
};

#endif // GAME_H_INCLUDED
