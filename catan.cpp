#include "catan.hpp"
#include <iostream>
#include <algorithm>
#include <cstdlib>

Catan::Catan(Player &player1, Player &player2, Player &player3) : currentPlayerIndex(0)
{
    players.push_back(player1);
    players.push_back(player2);
    players.push_back(player3);

    if (players.size() != 3)
    {
        throw std::runtime_error("Catan game requires exactly 3 players.");
    }

    // Randomly shuffle the players to determine the starting player
    std::random_shuffle(players.begin(), players.end());
    currentPlayerIndex = 0;
}

void Catan::ChooseStartingPlayer()
{
    std::cout << "Starting player: " << players[currentPlayerIndex].getName() << std::endl;
}

Board &Catan::getBoard()
{
    return board;
}

void Catan::playGame()
{
    bool gameWon = false;
    int rounds = 0; // Track the number of rounds played

    while (!gameWon)
    {
        printStatus();
        Player &currentPlayer = players[currentPlayerIndex];

        std::cout << currentPlayer.getName() << "'s turn:" << std::endl;
        currentPlayer.rollDice(board);
        // Add more actions (building, trading, using development cards) here

        currentPlayer.endTurn();
        if (currentPlayer.getVictoryPoints() >= 10)
        {
            std::cout << currentPlayer.getName() << " wins the game!" << std::endl;
            gameWon = true;
        }
        else
        {
            nextTurn();
        }

        rounds++;
    }

    if (!gameWon)
    {
        std::cout << "The game ended in a draw." << std::endl;
    }
}

void Catan::nextTurn()
{
    currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
}

void Catan::printStatus() const
{
    for (const auto &player : players)
    {
        player.printPoints();
    }
}
