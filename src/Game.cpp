#include "Game.h"
#include "Exceptions.h"

void Game::addPlayer(Player* p)
{
    players.push_back(p);
}

void Game::start()
{
    if(players.empty())
        throw game_init_error("No players for game");

    // Deal cards
    dealCards(players);

    unsigned int turn = 0;
    Player* p = players.front();
    while(!isOver())
    {
        p = players.at(turn);
        beforeCardPlayed(turn, players.size());
        int index = ui->requestCard(p->getHand());
        Card* c = p->getCard(index);
        if(valid(c))
            turn = ++turn % players.size();
        afterCardPlayed(p, players, c);
    }
    ui->showScores(players);
}

vector<Player*> Game::getPlayers(){
    return players;
}
