#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <list>
#include "Card.h"

class Player {
 public:
    explicit Player(const std::string& n) : name(n) {}
    virtual ~Player() {}
    void addCard(Card* c);
    Card* getCard(unsigned int index);
    std::list<Card*>* getHand();
    void addPoints(unsigned int points);

    /*!
       \brief   removes card from the player's hand
       \param   card    card to be removed
    */
    void removeCard(Card* card);
    unsigned int getScore();

    const std::string name;

 private:
    std::list<Card*> hand;
    unsigned int score = 0;
};

#endif // PLAYER_H
