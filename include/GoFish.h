#ifndef GOFISH_H
#define GOFISH_H

#include <Game.h>


class GoFish : public Game
{
    public:
        GoFish(GameUI* ui, Deck* d) : Game(ui, d){}
        virtual ~GoFish(){}

    protected:

    private:
};

#endif // GOFISH_H
