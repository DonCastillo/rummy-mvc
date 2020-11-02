#include <iostream>
#include "gtest/gtest.h"
#include "Deck.h"

TEST(DeckTest, DeckSize) {
    Deck d;
    d.createStandard();
    EXPECT_EQ(52, d.size());
}

TEST(DeckTest, DeckCard) {
    Deck d;
    d.createStandard();
    EXPECT_EQ(52, d.size());
    Card* c = d.getCard();
    EXPECT_EQ(51, d.size());
    delete c;
}


TEST(DeckTest, DeckShuffle) {
    Deck d1;
    d1.createStandard();
    Card* c = d1.getCard();
    EXPECT_EQ(Card::CLUB, c->suit);
    EXPECT_EQ(Card::ACE, c->rank);
    delete c;

    Deck d2;
    d2.createStandard();
    d2.shuffle();
    Card* c2 = d2.getCard();
    EXPECT_FALSE(Card::CLUB == c2->suit && Card::ACE == c2->rank);
    delete c2;
}

TEST(DeckTest, DeckEmpty) {
    Deck d;
    Card* c;
    unsigned int deckSize = d.size();
    for (unsigned int i=0; i < deckSize; i++) {
        c = d.getCard();
        delete c; // tear up card into little pieces
    }

    EXPECT_TRUE(d.getCard() == nullptr);
    EXPECT_TRUE(d.getCard() == nullptr);
}
