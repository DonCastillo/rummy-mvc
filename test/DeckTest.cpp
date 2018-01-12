#include "gtest/gtest.h"
#include "Deck.h"

#include <iostream>

TEST (DeckTest, DeckSize)
{
    Deck d;
    EXPECT_EQ(52, d.size());
}

TEST (DeckTest, DeckCard)
{
    Deck d;
    EXPECT_EQ(52, d.size());
    d.getCard();
    EXPECT_EQ(51, d.size());
}


TEST (DeckTest, DeckShuffle)
{
    Deck d1;
    Card* c = d1.getCard();
    EXPECT_EQ(Card::CLUB, c->suit);
    EXPECT_EQ(Card::ACE, c->rank);

    //cout << *c << endl;

    Deck d2;
    d2.shuffle();
    c = d2.getCard();

    EXPECT_FALSE(Card::CLUB == c->suit && Card::ACE == c->rank);

    //cout << *c << endl;
}

TEST (DeckTest, DeckEmpty)
{
    Deck d;
    unsigned int deckSize = d.size();
    for(unsigned int i=0; i < deckSize; i++)
    {
        d.getCard();
    }

    EXPECT_TRUE(d.getCard() == nullptr);
    EXPECT_TRUE(d.getCard() == nullptr);

    //cout << *c << endl;
}
