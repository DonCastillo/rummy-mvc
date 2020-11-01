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
  .Times(20);

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
  .Times(21);

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
  .Times(28);

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
  .Times(30);

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
  .Times(36);

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
