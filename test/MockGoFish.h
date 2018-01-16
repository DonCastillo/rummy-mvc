#ifndef MOCKGOFISH_H
#define MOCKGOFISH_H

#include "GoFish.h"
#include "NoUI.h"

class MockGoFish : public GoFish
{
    public:
        explicit MockGoFish(Deck* d):GoFish(new NoUi(),d){playerAsked = 1;}
        virtual ~MockGoFish(){}
        //beforeCardPlayed(unsigned int playerNum, unsigned int numPlayers);
        //MOCK_METHOD2(beforeCardPlayed, void());

    protected:

    private:
};

#endif // MOCKGOFISH_H
