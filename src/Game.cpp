#include "Game.h"
#include "Exceptions.h"

bool Game::isOver() const
{
    for(Player* p : players)
        if(p->getHand()->empty())
            return true;
    return false;
}


bool Game::valid(Card* c)
{
    return c != nullptr;
}

void Game::addPlayer(Player* p)
{
    players.push_back(p);
}

void Game::start()
{
    if(players.empty())
        throw game_init_error("No players for game");

    // Deal cards
    deck->shuffle();
    dealCards(players);

    unsigned int turn = 0;
    Card* c;
    Player* p = players.front();
    while(!isOver())
    {
        p = players.at(turn);
        do
        {
            beforeCardPlayed(turn, players.size());
            int index = ui->requestCard(p->getHand());
            c = p->getCard(index);
            afterCardPlayed(p, players, c);
        }
        while(!turnOver());

        turn = ++turn % players.size();


    }
    ui->showScores(players);
}

vector<Player*> Game::getPlayers()
{
    return players;
}
