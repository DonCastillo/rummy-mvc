#include "gtest/gtest.h"

#include "MockDeck.h"
#include "MockUI.h"

#include "Card.h"
#include "Game.h"
#include "GoFish.h"

#include <iostream>

using ::testing::Return;
using ::testing::_;
using ::testing::Expectation;

class GoFishTest : public ::testing::Test {
 protected:

   virtual ~GoFishTest() {
     delete aceClub;
     delete aceDia;
     delete aceHeart;
     delete aceSpade;

     delete kingClub;
     delete kingDia;
     delete kingHeart;
     delete kingSpade;

     delete twoClub;
     delete twoDia;
     delete twoHeart;
     delete twoSpade;

     delete queenClub;
     delete queenDia;
     delete queenHeart;
     delete queenSpade;

     delete threeClub;
     delete threeDia;
     delete threeHeart;
     delete threeSpade;

     delete jackClub;
     delete jackHeart;
     delete jackSpade;

   }

   Card* aceClub = new Card(Card::CLUB, Card::ACE);
   Card* aceSpade = new Card(Card::SPADE, Card::ACE);
   Card* aceDia = new Card(Card::DIAMOND, Card::ACE);
   Card* aceHeart = new Card(Card::HEART, Card::ACE);

   Card* kingClub = new Card(Card::CLUB, Card::KING);
   Card* kingSpade = new Card(Card::SPADE, Card::KING);
   Card* kingDia = new Card(Card::DIAMOND, Card::KING);
   Card* kingHeart = new Card(Card::HEART, Card::KING);

   Card* twoClub = new Card(Card::CLUB, Card::TWO);
   Card* twoSpade = new Card(Card::CLUB, Card::TWO);
   Card* twoDia = new Card(Card::CLUB, Card::TWO);
   Card* twoHeart = new Card(Card::CLUB, Card::TWO);

   Card* queenClub = new Card(Card::CLUB, Card::QUEEN);
   Card* queenSpade = new Card(Card::CLUB, Card::QUEEN);
   Card* queenDia = new Card(Card::CLUB, Card::QUEEN);
   Card* queenHeart = new Card(Card::CLUB, Card::QUEEN);

   Card* threeClub = new Card(Card::CLUB, Card::THREE);
   Card* threeSpade = new Card(Card::CLUB, Card::THREE);
   Card* threeDia = new Card(Card::CLUB, Card::THREE);
   Card* threeHeart = new Card(Card::CLUB, Card::THREE);

   Card* jackClub = new Card(Card::CLUB, Card::JACK);
   Card* jackSpade = new Card(Card::CLUB, Card::JACK);
   Card* jackHeart = new Card(Card::CLUB, Card::JACK);
};

TEST_F(GoFishTest, CardDealSmall) {
    MockDeck d;

    EXPECT_CALL(d, getCard())
    .Times(14)
    .WillRepeatedly(Return(aceClub));

    EXPECT_CALL(d, size())
    .Times(1)
    .WillOnce(Return(14));

    MockUI ui;

    Game* game = new GoFish(&ui, &d);

    Player* player1 = new Player("John");
    Player* player2 = new Player("Danielle");
    game->addPlayer(player1);
    game->addPlayer(player2);

    game->dealCards(game->getPlayers());

    for (Player* p : game->getPlayers())
        EXPECT_EQ(7, p->getHand()->size());

    delete game;
    delete player1;
    delete player2;
}


TEST_F(GoFishTest, CardDealLarge) {
    MockDeck d;
    EXPECT_CALL(d, getCard())
    .Times(20)
    .WillRepeatedly(Return(aceHeart));

    EXPECT_CALL(d, size())
    .Times(1)
    .WillOnce(Return(20));

    MockUI ui;

    Game* game = new GoFish(&ui, &d);

    Player* player1 = new Player("John");
    Player* player2 = new Player("Danielle");
    Player* player3 = new Player("Tara");
    Player* player4 = new Player("Erik");
    game->addPlayer(player1);
    game->addPlayer(player2);
    game->addPlayer(player3);
    game->addPlayer(player4);

    game->dealCards(game->getPlayers());

    for (Player* p : game->getPlayers())
        EXPECT_EQ(5, p->getHand()->size());

    delete game;
    delete player1;
    delete player2;
    delete player3;
    delete player4;
}

TEST_F(GoFishTest, DrawSet) {
    MockDeck d;

    EXPECT_CALL(d, getCard())
    .Times(23)
    .After(EXPECT_CALL(d, shuffle()))
    // Hands
    .WillOnce(Return(aceClub))
    .WillOnce(Return(kingClub))
    .WillOnce(Return(aceSpade))
    .WillOnce(Return(kingSpade))
    .WillOnce(Return(aceDia))
    .WillOnce(Return(kingDia))

    .WillOnce(Return(twoClub))
    .WillOnce(Return(queenClub))
    .WillOnce(Return(twoSpade))
    .WillOnce(Return(queenSpade))
    .WillOnce(Return(twoDia))
    .WillOnce(Return(queenDia))

    .WillOnce(Return(threeClub))
    .WillOnce(Return(jackClub))

    // Deck
    .WillOnce(Return(aceHeart))
    .WillOnce(Return(kingHeart))
    .WillOnce(Return(twoHeart))
    .WillOnce(Return(queenHeart))
    .WillOnce(Return(threeHeart))
    .WillOnce(Return(jackHeart))
    .WillOnce(Return(threeDia))
    .WillOnce(Return(jackSpade))
    .WillOnce(Return(threeSpade));

    EXPECT_CALL(d, size())
    .Times(1)
    .WillOnce(Return(23));

    MockUI ui;

    EXPECT_CALL(ui, choosePlayer(_ , _))
    .Times(9)
    .WillOnce(Return(1))
    .WillOnce(Return(0))
    .WillOnce(Return(1))
    .WillOnce(Return(0))
    .WillOnce(Return(1))
    .WillOnce(Return(0))
    .WillOnce(Return(1))
    .WillOnce(Return(0))
    .WillOnce(Return(1));

    EXPECT_CALL(ui, playFailed())
    .Times(9);

    EXPECT_CALL(ui, requestCard(_))
    .Times(9);

    EXPECT_CALL(ui, showScores(_))
    .Times(1);

    Game* game = new GoFish(&ui, &d);

    Player* player1 = new Player("John");
    Player* player2 = new Player("Kira");

    game->addPlayer(player1);
    game->addPlayer(player2);
    game->start();

    EXPECT_EQ(3, player1->getScore());

    delete game;
    delete player1;
    delete player2;
}

TEST_F(GoFishTest, AfterCardPlayedSet) {
    MockDeck d;

    EXPECT_CALL(d, getCard())
    .Times(15)
    .After(EXPECT_CALL(d, shuffle()))
    // Hands
    .WillOnce(Return(aceClub))
    .WillOnce(Return(kingClub))
    .WillOnce(Return(aceDia))
    .WillOnce(Return(kingDia))
    .WillOnce(Return(aceHeart))
    .WillOnce(Return(kingHeart))

    .WillOnce(Return(twoClub))
    .WillOnce(Return(queenClub))
    .WillOnce(Return(twoHeart))
    .WillOnce(Return(queenHeart))
    .WillOnce(Return(twoSpade))
    .WillOnce(Return(queenSpade))

    .WillOnce(Return(kingSpade))
    .WillOnce(Return(aceSpade))

    // Deck
    .WillOnce(Return(twoDia));

    EXPECT_CALL(d, size())
    .Times(1)
    .WillOnce(Return(15));

    MockUI ui;

    EXPECT_CALL(ui, choosePlayer(_, _))
    .Times(3)
    .WillOnce(Return(1))
    .WillOnce(Return(0))
    .WillOnce(Return(1));

    EXPECT_CALL(ui, playFailed())
    .Times(1);

    EXPECT_CALL(ui, playSucceeded())
    .Times(2);

    EXPECT_CALL(ui, requestCard(_))
    .Times(3);

    EXPECT_CALL(ui, showScores(_))
    .Times(1);


    Game* game = new GoFish(&ui, &d);

    Player* player1 = new Player("John");
    Player* player2 = new Player("Kira");

    game->addPlayer(player1);
    game->addPlayer(player2);
    game->start();

    EXPECT_EQ(2, player1->getScore());

    delete game;
    delete player1;
    delete player2;
}
