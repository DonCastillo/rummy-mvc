#include "gtest/gtest.h"
#include "MockGoFish.h"
#include "Deck.h"
#include "Card.h"

Deck* createDeck()
{
    vector<Card::Suit> suits;
    suits.push_back(Card::CLUB);
    suits.push_back(Card::DIAMOND);
    suits.push_back(Card::SPADE);
    suits.push_back(Card::HEART);

    vector<Card::Rank> ranks;
    ranks.push_back(Card::ACE);
    ranks.push_back(Card::TWO);
    ranks.push_back(Card::THREE);
    ranks.push_back(Card::FOUR);
    ranks.push_back(Card::FIVE);

    Deck* deck = new Deck();
    for(vector<Card::Rank>::iterator rank = ranks.begin(); rank != ranks.end(); ++rank)
        for(vector<Card::Suit>::iterator suit = suits.begin(); suit != suits.end(); ++suit)
            deck->addCard(new Card(*suit, *rank));

    return deck;
}

TEST (GoFishTest, CardDealSmall)
{
    Game* game = new MockGoFish(createDeck());
    game->addPlayer(new Player("John"));
    game->addPlayer(new Player("Danielle"));

    game->dealCards(game->getPlayers());

    for(Player* p : game->getPlayers())
        EXPECT_TRUE(p->getHand()->size() == 7);
}

TEST (GoFishTest, CardDealLarge)
{
    Game* game = new MockGoFish(createDeck());
    game->addPlayer(new Player("John"));
    game->addPlayer(new Player("Danielle"));
    game->addPlayer(new Player("Tara"));
    game->addPlayer(new Player("Erik"));

    game->dealCards(game->getPlayers());

    for(Player* p : game->getPlayers())
        EXPECT_TRUE(p->getHand()->size() == 5);

    delete game;
}

TEST (GoFishTest, AfterCardPlayedDraw)
{
    Deck* deck = createDeck();
    Game* game = new MockGoFish(deck);
    Player* player1 = new Player("John");
    Player* player2 = new Player("Kira");
    game->addPlayer(player1);
    game->addPlayer(player2);

    for(unsigned int i=0; i<3; i++)
        player1->addCard(deck->getCard());

    Card* card = player1->getCard(0);
    EXPECT_TRUE(card->rank == Card::ACE);
    EXPECT_TRUE(card->suit == Card::CLUB);

    card = player1->getCard(2);
    EXPECT_TRUE(Card::getRank(card->rank) == "Ace");
    EXPECT_TRUE(Card::getSuit(card->suit) == "S");

    card = player1->getCard(3);
    EXPECT_TRUE(card == nullptr);

    game->afterCardPlayed(player1, game->getPlayers(), new Card(Card::CLUB, Card::SIX));
    EXPECT_EQ(1, player1->getScore());
    EXPECT_TRUE(game->isOver());
}

TEST (GoFishTest, AfterCardPlayedSet)
{
    Deck* deck = createDeck();
    Game* game = new MockGoFish(deck);
    Player* player1 = new Player("John");
    Player* player2 = new Player("Kira");
    game->addPlayer(player1);
    game->addPlayer(player2);

    for(unsigned int i=0; i<3; i++)
        player1->addCard(deck->getCard());
    Card* completeSet = deck->getCard();
    player2->addCard(completeSet);

    game->afterCardPlayed(player1, game->getPlayers(), completeSet);
    EXPECT_EQ(1, player1->getScore());
}

