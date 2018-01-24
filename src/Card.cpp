#include "Card.h"

string Card::getRank(const Card::Rank rank)
{
    switch(rank)
    {
    case Card::ACE :
        return "Ace";
    case Card::TWO :
        return "2";
    case Card::THREE :
        return "3";
    case Card::FOUR :
        return "4";
    case Card::FIVE :
        return "5";
    case Card::SIX :
        return "6";
    case Card::SEVEN :
        return "7";
    case Card::EIGHT :
        return "8";
    case Card::NINE :
        return "9";
    case Card::TEN :
        return "T";
    case Card::JACK :
        return "J";
    case Card::QUEEN :
        return "Q";
    case Card::KING :
        return "K";
    }
    return "?";
}

string Card::getSuit(const Card::Suit suit)
{
    switch(suit)
    {
    case Card::CLUB:
        return "C";
    case Card::DIAMOND:
        return "D";
    case Card::SPADE:
        return "S";
    case Card::HEART:
        return "H";
    }
    return "?";
}

ostream& operator<<(ostream& os, const Card& c)
{
    os << Card::getRank(c.rank) << ":" << Card::getSuit(c.suit);
    return os;
}

Card::Rank Card::nextRank(Card::Rank rank)
{
    switch(rank)
    {
    case Card::ACE:
        return Card::TWO;
    case Card::TWO:
        return Card::THREE;
    case Card::THREE:
        return Card::FOUR;
    case Card::FOUR:
        return Card::FIVE;
    case Card::FIVE:
        return Card::SIX;
    case Card::SIX:
        return Card::SEVEN;
    case Card::SEVEN:
        return Card::EIGHT;
    case Card::EIGHT:
        return Card::NINE;
    case Card::NINE:
        return Card::TEN;
    case Card::TEN:
        return Card::JACK;
    case Card::JACK:
        return Card::QUEEN;
    case Card::QUEEN:
        return Card::KING;
    case Card::KING:
        return Card::ACE;
    }
}
