#include <vector>
#include "gtest/gtest.h"
#include "MockDeck.h"
#include "MockUI.h"
#include "Player.h"
#include "Rummy.h"


using ::testing::Return;
using ::testing::_;
using ::testing::Expectation;

// deal with 2 players
TEST(RummyTest, deal_cards_with_2_players) {
  MockDeck d;
  MockUI ui;

  EXPECT_CALL(d, getCard())
  .Times(21);

  EXPECT_CALL(d, size())
  .Times(1)
  .WillOnce(Return(32));

  Game* game = new Rummy(&ui, &d);
  Player* michael = new Player("Michael");
  Player* dwight = new Player("Dwight");

  // no players yet
  EXPECT_EQ(game->getPlayers().size(), 0);

  game->addPlayer(michael);
  game->addPlayer(dwight);

  // with 2 players
  EXPECT_EQ(game->getPlayers().size(), 2);

  game->dealCards(game->getPlayers());

  for (Player* p : game->getPlayers())
    EXPECT_EQ(10, p->getHand()->size());

  delete game;
  delete michael;
  delete dwight;
}

// deal with 3 players
TEST(RummyTest, deal_cards_with_3_players) {
  MockDeck d;
  MockUI ui;

  EXPECT_CALL(d, getCard())
  .Times(22);

  EXPECT_CALL(d, size())
  .Times(1)
  .WillOnce(Return(31));

  Game* game = new Rummy(&ui, &d);
  Player* michael = new Player("Michael");
  Player* dwight = new Player("Dwight");
  Player* jim = new Player("Jim");

  game->addPlayer(michael);
  game->addPlayer(dwight);
  game->addPlayer(jim);

  EXPECT_EQ(game->getPlayers().size(), 3);

  game->dealCards(game->getPlayers());

  for (Player* p : game->getPlayers())
    EXPECT_EQ(7, p->getHand()->size());

  delete game;
  delete jim;
  delete michael;
  delete dwight;
}

// deal with 4 players
TEST(RummyTest, deal_cards_with_4_players) {
  MockDeck d;
  MockUI ui;

  EXPECT_CALL(d, getCard())
  .Times(29);

  EXPECT_CALL(d, size())
  .Times(1)
  .WillOnce(Return(24));

  Game* game = new Rummy(&ui, &d);
  Player* michael = new Player("Michael");
  Player* dwight = new Player("Dwight");
  Player* jim = new Player("Jim");
  Player* pam = new Player("Pam");

  game->addPlayer(michael);
  game->addPlayer(dwight);
  game->addPlayer(jim);
  game->addPlayer(pam);

  EXPECT_EQ(game->getPlayers().size(), 4);

  game->dealCards(game->getPlayers());

  for (Player* p : game->getPlayers())
    EXPECT_EQ(7, p->getHand()->size());

  delete game;
  delete jim;
  delete pam;
  delete michael;
  delete dwight;
}

// deal with 5 players
TEST(RummyTest, deal_cards_with_5_players) {
  MockDeck d;
  MockUI ui;

  EXPECT_CALL(d, getCard())
  .Times(31);

  EXPECT_CALL(d, size())
  .Times(1)
  .WillOnce(Return(22));

  Game* game = new Rummy(&ui, &d);
  Player* michael = new Player("Michael");
  Player* dwight = new Player("Dwight");
  Player* jim = new Player("Jim");
  Player* pam = new Player("Pam");
  Player* erin = new Player("Erin");


  game->addPlayer(michael);
  game->addPlayer(dwight);
  game->addPlayer(jim);
  game->addPlayer(pam);
  game->addPlayer(erin);

  EXPECT_EQ(game->getPlayers().size(), 5);

  game->dealCards(game->getPlayers());

  for (Player* p : game->getPlayers())
    EXPECT_EQ(6, p->getHand()->size());

  delete game;
  delete erin;
  delete jim;
  delete pam;
  delete michael;
  delete dwight;
}

// deal with 6 players
TEST(RummyTest, deal_cards_with_6_players) {
  MockDeck d;
  MockUI ui;

  EXPECT_CALL(d, getCard())
  .Times(37);

  EXPECT_CALL(d, size())
  .Times(1)
  .WillOnce(Return(16));

  Game* game = new Rummy(&ui, &d);
  Player* michael = new Player("Michael");
  Player* dwight = new Player("Dwight");
  Player* jim = new Player("Jim");
  Player* pam = new Player("Pam");
  Player* erin = new Player("Erin");
  Player* ryan = new Player("Ryan");

  game->addPlayer(michael);
  game->addPlayer(dwight);
  game->addPlayer(jim);
  game->addPlayer(pam);
  game->addPlayer(erin);
  game->addPlayer(ryan);

  EXPECT_EQ(game->getPlayers().size(), 6);

  game->dealCards(game->getPlayers());

  for (Player* p : game->getPlayers())
    EXPECT_EQ(6, p->getHand()->size());

  delete game;
  delete ryan;
  delete erin;
  delete jim;
  delete pam;
  delete michael;
  delete dwight;
}

TEST(RummyTest, draw_card_from_deck_or_discard_pile) {
  Deck* d = new Deck();
  MockUI ui;

  Rummy* game = new Rummy(&ui, d);
  Player* michael = new Player("Michael");
  Player* dwight = new Player("Dwight");
  game->addPlayer(michael);
  game->addPlayer(dwight);
  game->dealCards(game->getPlayers());

  // before drawing
  EXPECT_EQ(game->getDeck()->size(), 31);
  EXPECT_EQ(game->getDiscardPile().size(), 1);

  // draw from the deck
  game->drawCard(michael, 0);
  EXPECT_EQ(michael->getHand()->size(), 11);  // michael's hand
  EXPECT_EQ(game->getDeck()->size(), 30); // current deck

  delete michael;
  delete dwight;
  delete game;
  delete d;
}
