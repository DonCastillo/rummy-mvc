#include "Deck.h"

#include <vector>
#include <random>

#include <iostream>

void Deck::addCard(Card* card)
{
    deck.push_back(card);
}

void Deck::createStandard()
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
    ranks.push_back(Card::SIX);
    ranks.push_back(Card::SEVEN);
    ranks.push_back(Card::EIGHT);
    ranks.push_back(Card::NINE);
    ranks.push_back(Card::TEN);
    ranks.push_back(Card::JACK);
    ranks.push_back(Card::QUEEN);
    ranks.push_back(Card::KING);

    for(vector<Card::Suit>::iterator suit = suits.begin(); suit != suits.end(); ++suit)
        for(vector<Card::Rank>::iterator rank = ranks.begin(); rank != ranks.end(); ++rank)
            addCard(new Card(*suit, *rank));
}

Card* Deck::getCard()
{
    if(deck.empty())
        return nullptr;

    Card* card = deck.front();
    deck.pop_front();
    return card;
}

void Deck::shuffle()
{
    list<Card*> shuffledDeck;

    while(deck.size() > 0)
    {
        //cout << "Selecting card" << endl;
        int selection = rand() % deck.size();

        //cout << "Selecting #" << selection << endl;

        list<Card*>::iterator card = deck.begin();
        for(int i=0; i<selection; i++)
            card = ++card;
        //cout << "Adding " << **card << endl;

        shuffledDeck.push_back(*card);
        deck.erase(card);
    }

    deck.clear();
    //copy(shuffledDeck.begin(), shuffledDeck.end(), deck);
    for(list<Card*>::iterator card = shuffledDeck.begin(); card != shuffledDeck.end(); ++card)
        deck.push_back(*card);
}

unsigned int Deck::size()
{
    return deck.size();
}
