#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED

#include <iostream>
#include <string>

class Card {
 public:
    enum Suit {CLUB, DIAMOND, SPADE, HEART};
    enum Rank {ACE, TWO, THREE, FOUR, FIVE, SIX,
      SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};

    Card(Suit s, Rank r):suit(s), rank(r) {}
    static std::string getRank(Card::Rank r);
    static std::string getSuit(Card::Suit s);

    /*!
       \brief   returns the succeeding rank of the passed rank
       \param   r   card rank to be examined
       \return  rank that succeedes the rank passed (e.g. QUEEN -> KING)
    */
    static Rank nextRank(Rank r);

    /*!
       \brief   returns the preceding rank of the passed rank
       \param   r   card rank to be examined
       \return  rank that precedes the rank passed (e.g. KING -> QUEEN)
    */
    static Rank prevRank(Rank r);

    /*!
       \brief   converts card rank into its equivalent numerical value
       \param   r   card rank
       \return  integer value of the passed card rank
    */
    static unsigned int numRank(Rank r);

    const Suit suit;
    const Rank rank;

    friend std::ostream& operator<<(std::ostream& os, const Card& c);

    /*!
       \brief   compares first card if it is greater than
                the second card in rank
       \param   a   first card
                b   second card
       \return  true if first card is greater than the second
                card, otherwise false
    */
    friend bool operator> (Card const &a, Card const &b);

    /*!
       \brief   compares first card if it is less than
                to the second card in rank
       \param   a   first card
                b   second card
       \return  true if first card is less than the second
                card, otherwise false
    */
    friend bool operator< (Card const &a, Card const &b);

    /*!
       \brief   compares first card if it is greater than or
                equal to the second card in rank
       \param   a   first card
                b   second card
       \return  true if first card is greater than or equal to
                the second card, otherwise false
    */
    friend bool operator>= (Card const &a, Card const &b);

    /*!
       \brief   compares first card if it is less than or
                equal to the second card in rank
       \param   a   first card
                b   second card
       \return  true if first card is less than or equal to
                the second card, otherwise false
    */
    friend bool operator<= (Card const &a, Card const &b);

    /*!
       \brief   compares two cards if they are equal in rank
       \param   a   first card
                b   second card
       \return  true if they are equal, otherwise false
    */
    friend bool operator== (Card const &a, Card const &b);

    /*!
       \brief   compares two cards if they are not equal in rank
       \param   a   first card
                b   second card
       \return  true if they are not equal, otherwise false
    */
    friend bool operator!= (Card const &a, Card const &b);
};

#endif // CARD_H_INCLUDED
