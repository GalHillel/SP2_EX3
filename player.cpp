#include "player.hpp"
#include "board.hpp"
#include "catan.hpp"
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <ctime>
#include <cstdlib>

Player::Player(const std::string &name) : name(name), victoryPoints(2)
{
    resources = {{"wood", 1}, {"brick", 1}, {"wool", 1}, {"oat", 1}, {"iron", 1}};
}

void Player::placeSettlement(const std::string &location, Board &board)
{
    if (board.isSettlementPlaceable(location) && resources["wood"] >= 1 && resources["brick"] >= 1 && resources["wool"] >= 1 && resources["oat"] >= 1)
    {
        settlements.push_back(location);
        resources["wood"] -= 1;
        resources["brick"] -= 1;
        resources["wool"] -= 1;
        resources["oat"] -= 1;
        addVictoryPoints(1);
        std::cout << name << " placed a settlement at " << location << std::endl;
    }
    else
    {
        throw std::runtime_error("Invalid placement for settlement or insufficient resources.");
    }
}

void Player::placeRoad(const std::string &startLocation, const std::string &endLocation, Board &board)
{
    if (board.isRoadPlaceable(startLocation, endLocation) && resources["wood"] >= 1 && resources["brick"] >= 1)
    {
        roads.push_back({startLocation, endLocation});
        resources["wood"] -= 1;
        resources["brick"] -= 1;
        std::cout << name << " placed a road from " << startLocation << " to " << endLocation << std::endl;
    }
    else
    {
        throw std::runtime_error("Invalid placement for road or insufficient resources.");
    }
}

void Player::placeCity(const std::string &location, Board &board)
{
    if (std::find(settlements.begin(), settlements.end(), location) != settlements.end() &&
        resources["iron"] >= 3 && resources["oat"] >= 2)
    {
        resources["iron"] -= 3;
        resources["oat"] -= 2;
        settlements.erase(std::remove(settlements.begin(), settlements.end(), location), settlements.end());
        cities.push_back(location);
        board.upgradeSettlementToCity(location);
        std::cout << name << " upgraded settlement to city at " << location << std::endl;
    }
    else
    {
        throw std::runtime_error("Cannot upgrade settlement to city or insufficient resources.");
    }
}

void Player::rollDice(Board &board)
{
    int roll1 = std::rand() % 6 + 1;
    int roll2 = std::rand() % 6 + 1;
    int result = roll1 + roll2;
    std::cout << name << " rolled a " << result << std::endl;

    for (const auto &settlement : settlements)
    {
        std::string hexagon = board.getHexagonByNumber(result);
        std::string resource = board.getResource(hexagon);
        if (!resource.empty())
        {
            resources[resource]++;
            std::cout << name << " collected " << resource << " from " << hexagon << std::endl;
        }
    }

    for (const auto &city : cities)
    {
        std::string hexagon = board.getHexagonByNumber(result);
        std::string resource = board.getResource(hexagon);
        if (!resource.empty())
        {
            resources[resource] += 2; // Cities collect double resources
            std::cout << name << " collected " << resource << " from " << hexagon << std::endl;
        }
    }
}

void Player::trade(Player &other, const std::string &giveResource, const std::string &receiveResource, int giveAmount, int receiveAmount)
{
    if (resources[giveResource] >= giveAmount && other.resources[receiveResource] >= receiveAmount)
    {
        resources[giveResource] -= giveAmount;
        resources[receiveResource] += receiveAmount;
        other.resources[giveResource] += giveAmount;
        other.resources[receiveResource] -= receiveAmount;
        std::cout << name << " traded " << giveAmount << " " << giveResource << " for " << receiveAmount << " " << receiveResource << " with " << other.getName() << std::endl;
    }
    else
    {
        throw std::runtime_error("Insufficient resources for trade.");
    }
}

void Player::buyDevelopmentCard()
{
    if (resources["iron"] >= 1 && resources["wool"] >= 1 && resources["oat"] >= 1)
    {
        resources["iron"] -= 1;
        resources["wool"] -= 1;
        resources["oat"] -= 1;
        std::vector<std::string> developmentCardTypes = {"Promotion", "Knight", "Victory Point"};
        auto randomIndex = static_cast<std::vector<std::string>::size_type>(std::rand() % static_cast<int>(developmentCardTypes.size()));
        std::string cardType = developmentCardTypes[randomIndex];
        developmentCards.push_back(cardType);
        std::cout << name << " bought a development card of type: " << cardType << std::endl;
    }
    else
    {
        throw std::runtime_error("Insufficient resources to buy a development card.");
    }
}

void Player::useDevelopmentCard(const std::string &card, Catan &game)
{
    auto it = std::find(developmentCards.begin(), developmentCards.end(), card);
    if (it != developmentCards.end())
    {
        if (card == "Promotion")
        {
            // Implementing Monopoly, Building Roads, Year of Plenty

            // Monopoly: Choose a resource and get all of it from other players
            std::cout << "Choose a resource for Monopoly (wood, brick, wool, oat, iron): ";
            std::string chosenResource;
            std::cin >> chosenResource;

            for (auto &player : game.players)
            {
                if (player.getName() != name)
                {
                    resources[chosenResource] += player.resources[chosenResource];
                    player.resources[chosenResource] = 0;
                }
            }
            std::cout << name << " used Monopoly to collect all " << chosenResource << " from other players." << std::endl;

            // Building Roads: Player can build 2 roads at no cost
            std::cout << "You can build 2 roads at no cost." << std::endl;
            for (int i = 0; i < 2; ++i)
            {
                std::string start, end;
                std::cout << "Enter the start and end locations for road " << i + 1 << ": ";
                std::cin >> start >> end;
                placeRoad(start, end, game.getBoard());
            }

            // Year of Plenty: Receive any 2 resources from the bank
            std::cout << "Choose any 2 resources to receive from the bank (wood, brick, wool, oat, iron): ";
            for (int i = 0; i < 2; ++i)
            {
                std::string resource;
                std::cin >> resource;
                resources[resource]++;
            }
            std::cout << name << " used Year of Plenty to receive 2 resources from the bank." << std::endl;
        }
        else if (card == "Knight")
        {
            knightCardCount++;
            std::cout << name << " used a Knight card." << std::endl;
            if (knightCardCount == 3)
            {
                largestArmyOwner = name;
                addVictoryPoints(2);
                std::cout << name << " now has the largest army and gained 2 victory points." << std::endl;
            }
        }
        else if (card == "Victory Point")
        {
            addVictoryPoints(1);
        }
        developmentCards.erase(it);
        std::cout << name << " used a development card of type: " << card << std::endl;
    }
    else
    {
        throw std::runtime_error("Player does not have the specified development card.");
    }
}

void Player::endTurn()
{
    std::cout << name << " ended their turn." << std::endl;
}

void Player::printPoints() const
{
    std::cout << name << " has " << victoryPoints << " victory points." << std::endl;
}

const std::string &Player::getName() const
{
    return name;
}

int Player::getVictoryPoints() const
{
    return victoryPoints;
}

void Player::addVictoryPoints(int points)
{
    victoryPoints += points;
}

void Player::subtractVictoryPoints(int points)
{
    victoryPoints -= points;
}

void Player::addResource(const std::string &resource, int amount)
{
    resources[resource] += amount;
}

void Player::subtractResource(const std::string &resource, int amount)
{
    resources[resource] -= amount;
}

const std::unordered_map<std::string, int> &Player::getResources() const
{
    return resources;
}
