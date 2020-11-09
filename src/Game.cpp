#include "Game.h"
#include "Exceptions.h"
#include <vector>

bool Game::isOver() const {
    for (Player* p : players)
        if (p->getHand()->empty())
            return true;
    return false;
}

void Game::addPlayer(Player* p) {
    players.push_back(p);
}

std::vector<Player*> Game::getPlayers() {
    return players;
}
