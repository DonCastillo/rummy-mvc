#ifndef MOCKUI_H_INCLUDED
#define MOCKUI_H_INCLUDED

#include "GameUI.h"

class MockUI : public GameUI
{

public:
    MockUI() {}
    virtual ~MockUI() {}

    MOCK_METHOD1(requestCard, unsigned int(list<Card*>* hand));
    MOCK_METHOD0(playFailed, void());
    MOCK_METHOD0(playSucceeded, void());
    MOCK_METHOD2(choosePlayer, unsigned int(unsigned int playerNum, unsigned int numPlayers));
    MOCK_METHOD1(showScores, void(vector<Player*>));
};


#endif // MOCKUI_H_INCLUDED
