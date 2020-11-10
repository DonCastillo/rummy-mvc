#include "GameUI.h"
#include "Card.h"
#include "Deck.h"
#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
#include <cctype>
#include <list>

bool choiceValid(std::string choice, unsigned int choicesSize);

unsigned int GameUI::choosePlayer(unsigned int playerNum,
                                  unsigned int numPlayers) {
    unsigned int selection = playerNum;
    std::cout << "You are Player #" << playerNum << std::endl;
    while (selection == playerNum || selection >= numPlayers) {
        std::cout << "Which player (0-" << numPlayers-1 << ")? ";
        std::cin >> selection;
        if (selection == playerNum)
            std::cout << "That is you! Please choose another player."
              << std::endl;
        if (selection >= numPlayers)
            std::cout << "Player #" << selection <<
                 " doesn't exist! Please choose another player." << std::endl;
    }
    return selection;
}

void GameUI::showScores(std::vector<Player*> players) {
    std::cout << "---- Scores ----" << std::endl;
    for (Player* player : players)
        std::cout << player->name << ": " << player->getScore() << std::endl;
}


unsigned int GameUI::choose(std::vector<std::string> choices) {
    std::string choice;
    for (int i = 0; i < choices.size(); ++i) {
        std::cout << "Choose " << i << ": " << choices[i] << std::endl;
    }


    do {
        std::cout << "Select a choice: ";
        std::getline(std::cin, choice);
    }while( !choiceValid(choice, choices.size()) );

    return std::stoul(choice, nullptr, 10);
}

void GameUI::println(std::string left, std::string right) {
    std::cout << left << ": " << right << std::endl;
}

void GameUI::print(std::string message) {
    std::cout << message;
}

void GameUI::println(std::string message) {
    std::cout << message << std::endl;
}

bool choiceValid(std::string choice, unsigned int choicesSize) {
    if (choice == "")
      return false;

    // check if it's not a digit
    for (char c : choice) {
        if (!isdigit(c))
            return false;
    }

    // check if it's out of range
    unsigned int choiceTemp = std::stoul(choice, nullptr, 10);
    if (choiceTemp < 0 || choiceTemp > (choicesSize - 1))
        return false;

    return true;
}
