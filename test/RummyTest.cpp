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
