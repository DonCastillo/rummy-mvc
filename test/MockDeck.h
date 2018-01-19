#ifndef MOCKDECK_H_INCLUDED
#define MOCKDECK_H_INCLUDED

#include "gmock/gmock.h"
#include "Deck.h"
#include "Card.h"

using namespace ::testing;

class MockDeck : public Deck
{
public:
    explicit MockDeck() {}
    virtual ~MockDeck() {}

    MOCK_METHOD0(getCard, Card*());

};

#endif // MOCKDECK_H_INCLUDED
