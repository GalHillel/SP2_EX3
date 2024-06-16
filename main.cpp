#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "board.hpp"
#include "player.hpp"
#include "catan.hpp"

// Function to print the player's resources
void printPlayerResources(const Player &player)
{
    std::cout << "Resources for " << player.getName() << ":" << std::endl;
    std::cout << "Wood: " << player.getResources()["wood"] << std::endl;
    std::cout << "Brick: " << player.getResources()["brick"] << std::endl;
    std::cout << "Wool: " << player.getResources()["wool"] << std::endl;
    std::cout << "Oat: " << player.getResources()["oat"] << std::endl;
    std::cout << "Iron: " << player.getResources()["iron"] << std::endl;
}

// Function to display the game board
void displayBoard(const Board &board)
{
    // Print the game board
}

// Function to display the available actions for a player's turn
void displayActions()
{
    std::cout << "Select an action:" << std::endl;
    std::cout << "1. Build Settlement" << std::endl;
    std::cout << "2. Build Road" << std::endl;
    std::cout << "3. Build City" << std::endl;
    std::cout << "4. Buy Development Card" << std::endl;
    std::cout << "5. Use Development Card" << std::endl;
    std::cout << "6. Trade with Other Players" << std::endl;
    std::cout << "7. End Turn" << std::endl;
}

int main()
{
    // Initialize random seed
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    Player p1("Gal");
    Player p2("Sharon");
    Player p3("Ori");

    // Create a Catan game
    Catan catan(p1, p2, p3);

    // Game loop
    while (true)
    {
        for (auto &player : catan.players)
        {
            // Display player's resources
            printPlayerResources(player);

            // Display game board
            displayBoard(catan.getBoard());

            // Display available actions
            displayActions();

            int choice;
            std::cin >> choice;

            switch (choice)
            {
            case 1:
            {
                std::string location;
                std::cout << "Enter location for settlement: ";
                std::cin >> location;
                player.placeSettlement(location, catan.getBoard());
            }
            break;
            case 2:
            {
                std::string startLocation, endLocation;
                std::cout << "Enter start location for road: ";
                std::cin >> startLocation;
                std::cout << "Enter end location for road: ";
                std::cin >> endLocation;
                player.placeRoad(startLocation, endLocation, catan.getBoard());
            }
            break;
            case 3:
            {
                std::string location;
                std::cout << "Enter location for city: ";
                std::cin >> location;
                player.placeCity(location, catan.getBoard());
            }
            break;
            case 4:
                player.buyDevelopmentCard();
                break;
            case 5:
            {
                std::string cardType;
                std::cout << "Enter development card type: ";
                std::cin >> cardType;
                player.useDevelopmentCard(cardType, catan);
            }
            break;
            case 6:
            {
                std::cout << "Select a player to trade with:" << std::endl;
                for (size_t i = 0; i < catan.players.size(); ++i)
                {
                    std::cout << i + 1 << ". " << catan.players[i].getName() << std::endl;
                }
                int tradeChoice;
                std::cin >> tradeChoice;
                if (tradeChoice > 0 && tradeChoice <= catan.players.size())
                {
                    Player &tradePlayer = catan.players[tradeChoice - 1];
                    player.trade(tradePlayer);
                }
                else
                {
                    std::cout << "Invalid player choice." << std::endl;
                }
            }
            break;

            case 7:
                player.endTurn();
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
            }

            // Check for victory condition
            if (player.getVictoryPoints() >= 10)
            {
                std::cout << player.getName() << " wins the game!" << std::endl;
                return 0;
            }
        }
    }

    return 0;
}
