#ifndef PLAYER_H
#define PLAYER_H

using namespace std;

#include <string>
#include <list>
#include "Card.h"

class Player {
  public:
    explicit Player(const string& n) : name(n) {}
    virtual ~Player() {}
    void addCard(Card* c);
    Card* getCard(unsigned int index);
    list<Card*>* getHand();
    void addPoints(unsigned int points);
    unsigned int getScore();

    const string name;

  protected:

  private:
    list<Card*> hand;
    unsigned int score = 0;
};

#endif // PLAYER_H
