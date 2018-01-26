#include "gtest/gtest.h"

#include "MockDeck.h"
#include "MockUI.h"

#include "Cheat.h"

using namespace ::testing;

unsigned int deckSize;

void reduceDeckSize()
{
    deckSize--;
}

TEST (CheatTest, CardDeal4Player)
{
    MockDeck d;
    deckSize = 52;

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

TEST (CheatTest, NoCheatCalled)
{
    MockDeck d;
    deckSize = 3;

    EXPECT_CALL(d, size())
    .Times(4)
    .WillRepeatedly(ReturnPointee(&deckSize));

    EXPECT_CALL(d, getCard())
    .Times(3)
    .After(EXPECT_CALL(d, shuffle()))
    // Hands
    .WillOnce(DoAll(Invoke(reduceDeckSize),Return(new Card(Card::CLUB, Card::ACE))))
    .WillOnce(DoAll(Invoke(reduceDeckSize),Return(new Card(Card::CLUB, Card::TWO))))
    .WillOnce(DoAll(Invoke(reduceDeckSize),Return(new Card(Card::CLUB, Card::THREE))));


    MockUI ui;
    EXPECT_CALL(ui, choosePlayer(_,_))
    .Times(1)
    .WillOnce(Return(3));

    EXPECT_CALL(ui, showScores(_))
    .Times(1);

    EXPECT_CALL(ui, requestCard(_))
    .Times(2)
    .WillOnce(Return(0))
    .WillOnce(Return(-1));

    Game* game = new Cheat(&ui, &d);

    Player* player1 = new Player("John");
    Player* player2 = new Player("Kira");
    Player* player3 = new Player("Erik");

    game->addPlayer(player1);
    game->addPlayer(player2);
    game->addPlayer(player3);
    game->start();

    EXPECT_EQ(0, player1->getHand()->size());
    EXPECT_EQ(1, player2->getHand()->size());
    EXPECT_EQ(1, player3->getHand()->size());

    EXPECT_EQ(1, player1->getScore());
}

TEST (CheatTest, CheatCalledFalse)
{
    MockDeck d;
    deckSize = 3;

    EXPECT_CALL(d, size())
    .Times(4)
    .WillRepeatedly(ReturnPointee(&deckSize));

    EXPECT_CALL(d, getCard())
    .Times(3)
    .After(EXPECT_CALL(d, shuffle()))
    // Hands
    .WillOnce(DoAll(Invoke(reduceDeckSize),Return(new Card(Card::CLUB, Card::ACE))))
    .WillOnce(DoAll(Invoke(reduceDeckSize),Return(new Card(Card::CLUB, Card::TWO))))
    .WillOnce(DoAll(Invoke(reduceDeckSize),Return(new Card(Card::CLUB, Card::THREE))));


    MockUI ui;
    EXPECT_CALL(ui, choosePlayer(_,_))
    .Times(1)
    .WillOnce(Return(1));

    EXPECT_CALL(ui, showScores(_))
    .Times(1);

    EXPECT_CALL(ui, requestCard(_))
    .Times(2)
    .WillOnce(Return(0))
    .WillOnce(Return(-1));

    Game* game = new Cheat(&ui, &d);

    Player* player1 = new Player("John");
    Player* player2 = new Player("Kira");
    Player* player3 = new Player("Erik");

    game->addPlayer(player1);
    game->addPlayer(player2);
    game->addPlayer(player3);
    game->start();

    EXPECT_EQ(0, player1->getHand()->size());
    EXPECT_EQ(2, player2->getHand()->size());
    EXPECT_EQ(1, player3->getHand()->size());

    EXPECT_EQ(1, player1->getScore());
}

TEST (CheatTest, CheatCalledTrue)
{
    MockDeck d;
    deckSize = 3;

    EXPECT_CALL(d, size())
    .Times(4)
    .WillRepeatedly(ReturnPointee(&deckSize));

    EXPECT_CALL(d, getCard())
    .Times(3)
    .After(EXPECT_CALL(d, shuffle()))
    // Hands
    .WillOnce(DoAll(Invoke(reduceDeckSize),Return(new Card(Card::CLUB, Card::KING))))
    .WillOnce(DoAll(Invoke(reduceDeckSize),Return(new Card(Card::CLUB, Card::TWO))))
    .WillOnce(DoAll(Invoke(reduceDeckSize),Return(new Card(Card::CLUB, Card::THREE))));


    MockUI ui;
    EXPECT_CALL(ui, choosePlayer(_,_))
    .Times(2)
    .WillOnce(Return(1))
    .WillOnce(Return(3))
    ;

    EXPECT_CALL(ui, showScores(_))
    .Times(1);

    EXPECT_CALL(ui, requestCard(_))
    .Times(4)
    .WillOnce(Return(0))
    .WillOnce(Return(-1))
    .WillOnce(Return(0))
    .WillOnce(Return(-1));

    Game* game = new Cheat(&ui, &d);

    Player* player1 = new Player("John");
    Player* player2 = new Player("Kira");
    Player* player3 = new Player("Erik");

    game->addPlayer(player1);
    game->addPlayer(player2);
    game->addPlayer(player3);
    game->start();

    EXPECT_EQ(1, player1->getHand()->size());
    EXPECT_EQ(0, player2->getHand()->size());
    EXPECT_EQ(1, player3->getHand()->size());

    EXPECT_EQ(1, player2->getScore());
}
