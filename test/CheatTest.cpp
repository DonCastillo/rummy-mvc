#include "gtest/gtest.h"

#include "MockDeck.h"
#include "MockUI.h"

#include "Cheat.h"

using namespace ::testing;

unsigned int deckSize = 52;

void reduceDeckSize(){deckSize--;}

TEST (CheatTest, CardDeal4Player)
{
    MockDeck d;

    EXPECT_CALL(d, size())
    .Times(53)
    .WillRepeatedly(ReturnPointee(&deckSize));

    EXPECT_CALL(d, getCard())
    .Times(52)
    .WillRepeatedly(DoAll(Invoke(reduceDeckSize),Return(new Card(Card::CLUB, Card::ACE))));



    MockUI ui;

    Game* game = new Cheat(&ui, &d);

    game->addPlayer(new Player("John"));
    game->addPlayer(new Player("Danielle"));
    game->addPlayer(new Player("Kira"));
    game->addPlayer(new Player("Erik"));

    game->dealCards(game->getPlayers());

    for(Player* p : game->getPlayers())
        EXPECT_TRUE(p->getHand()->size() == 13);
}
