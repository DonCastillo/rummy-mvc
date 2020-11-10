#ifndef GAMEUI_H_INCLUDED
#define GAMEUI_H_INCLUDED

#include <list>
#include <vector>
#include <string>
#include "Card.h"
#include "Player.h"
#include "Deck.h"

class GameUI {
 public:
    GameUI() {}
    virtual ~GameUI() {}

    virtual unsigned int requestCard(std::list<Card*>* hand) = 0;
    virtual void playFailed() = 0;
    virtual void playSucceeded() = 0;
    virtual unsigned int choosePlayer(unsigned int playerNum,
                                      unsigned int numPlayers);
    virtual void showScores(std::vector<Player*> players);

    /*!
       \brief   asks user to choose among the items by entering the
                corresponding index starting at 0.
       \param   choices   list of choices to be presented to the user
       \return  returns the corresponding index of choice
    */
    static unsigned int choose(std::vector<std::string> choices);

    /*!
       \brief   prints two groups of text separated by a colon
       \param   left    text to be displayed on the left of the colon
                right   text to be displayed on the right of the colon
    */
    static void println(std::string left, std::string right);

    /*!
       \brief   prints text without new line at the end
       \param   string to be printed
    */
    static void print(std::string message);

    /*!
       \brief   prints text with new line at the end
       \param   string to be printed
    */
    static void println(std::string message);
};

#endif // GAMEUI_H_INCLUDED
