#include "Card.h"
#include <string>

//unsigned int numRank(Rank r);

std::string Card::getRank(const Card::Rank rank) {
    switch (rank) {
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

std::string Card::getSuit(const Card::Suit suit) {
    switch (suit) {
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

std::ostream& operator<<(std::ostream& os, const Card& c) {
    os << Card::getRank(c.rank) << ":" << Card::getSuit(c.suit);
    return os;
}

bool operator> (Card const &a, Card const &b) {
  if (Card::numRank(a.rank) > Card::numRank(b.rank))
      return true;
  else
      return false;
}

bool operator< (Card const &a, Card const &b) {
  if (Card::numRank(a.rank) < Card::numRank(b.rank))
      return true;
  else
      return false;
}

bool operator>= (Card const &a, Card const &b) {
  if (Card::numRank(a.rank) >= Card::numRank(b.rank))
      return true;
  else
      return false;
}

bool operator<= (Card const &a, Card const &b) {
  if (Card::numRank(a.rank) <= Card::numRank(b.rank))
      return true;
  else
      return false;
}

bool operator== (Card const &a, Card const &b) {
  if (Card::numRank(a.rank) == Card::numRank(b.rank))
      return true;
  else
      return false;
}

bool operator!= (Card const &a, Card const &b) {
  if (Card::numRank(a.rank) != Card::numRank(b.rank))
      return true;
  else
      return false;
}

Card::Rank Card::nextRank(Rank r) {
    switch (r) {
    case Card::ACE :
        return Card::TWO;
    case Card::TWO :
        return Card::THREE;
    case Card::THREE :
        return Card::FOUR;
    case Card::FOUR :
        return Card::FIVE;
    case Card::FIVE :
        return Card::SIX;
    case Card::SIX :
        return Card::SEVEN;
    case Card::SEVEN :
        return Card::EIGHT;
    case Card::EIGHT :
        return Card::NINE;
    case Card::NINE :
        return Card::TEN;
    case Card::TEN :
        return Card::JACK;
    case Card::JACK :
        return Card::QUEEN;
    case Card::QUEEN :
        return Card::KING;
    }
}

Card::Rank Card::prevRank(Rank r) {
    switch (r) {
    case Card::TWO :
        return Card::ACE;
    case Card::THREE :
        return Card::TWO;
    case Card::FOUR :
        return Card::THREE;
    case Card::FIVE :
        return Card::FOUR;
    case Card::SIX :
        return Card::FIVE;
    case Card::SEVEN :
        return Card::SIX;
    case Card::EIGHT :
        return Card::SEVEN;
    case Card::NINE :
        return Card::EIGHT;
    case Card::TEN :
        return Card::NINE;
    case Card::JACK :
        return Card::TEN;
    case Card::QUEEN :
        return Card::JACK;
    case Card::KING :
        return Card::QUEEN;
    }
}

unsigned int Card::numRank(Rank r) {
    switch (r) {
    case Card::ACE :
        return 1;
    case Card::TWO :
        return 2;
    case Card::THREE :
        return 3;
    case Card::FOUR :
        return 4;
    case Card::FIVE :
        return 5;
    case Card::SIX :
        return 6;
    case Card::SEVEN :
        return 7;
    case Card::EIGHT :
        return 8;
    case Card::NINE :
        return 9;
    case Card::TEN :
        return 10;
    case Card::JACK :
        return 11;
    case Card::QUEEN :
        return 12;
    case Card::KING :
        return 13;
    }
}
