#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED

#include <iostream>

using namespace std;

class Card
{

public:
    enum Suit {CLUB,DIAMOND,SPADE,HEART};
    enum Rank {ACE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,TEN,JACK,QUEEN,KING};

    Card(Suit s, Rank r):suit(s), rank(r) {}

    const Suit suit;
    const Rank rank;

    friend ostream& operator<<(ostream& os, const Card& c);
};


#endif // CARD_H_INCLUDED
