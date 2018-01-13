#include "GameUI.h"
#include <iostream>

unsigned int GameUI::choosePlayer(unsigned int playerNum, unsigned int numPlayers)
{

    unsigned int selection = playerNum;
    cout << "You are Player #" << playerNum << endl;
    while(selection == playerNum || selection >= numPlayers)
    {
        cout << "Which player (0-" << numPlayers-1 << ")? ";
        cin >> selection;
        if(selection == playerNum)
            cout << "That is you! Please choose another player." << endl;
        if(selection >= numPlayers)
            cout << "Player #" << selection << " doesn't exist! Please choose another player." << endl;
    }
    return selection;

}

void GameUI::showScores(vector<Player*> players){
    cout << "---- Scores ----" << endl;
    for(Player* player : players)
    cout << player->name << ": " << player->getScore() << endl;
}
