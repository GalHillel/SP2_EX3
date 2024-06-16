#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>
#include <unordered_map>

class Board;

class Player
{
public:
    Player(const std::string &name);

    void placeSettlement(const std::string &location, Board &board);
    void placeRoad(const std::string &startLocation, const std::string &endLocation, Board &board);
    void placeCity(const std::string &location, Board &board);
    void rollDice(Board &board);
    void trade(Player &other, const std::string &giveResource, const std::string &receiveResource, int giveAmount, int receiveAmount);
    void buyDevelopmentCard();
    void useDevelopmentCard(const std::string &card, Catan &game);
    void endTurn();
    void printPoints() const;

    const std::string &getName() const;
    int getVictoryPoints() const;
    void addVictoryPoints(int points);
    void subtractVictoryPoints(int points);
    void addResource(const std::string &resource, int amount);
    void subtractResource(const std::string &resource, int amount);
    const std::unordered_map<std::string, int> &getResources() const;

private:
    std::string name;
    std::string largestArmyOwner;
    int victoryPoints;
    int knightCardCount;
    std::unordered_map<std::string, int> resources;
    std::vector<std::string> settlements;
    std::vector<std::string> cities;
    std::vector<std::pair<std::string, std::string>> roads;
    std::vector<std::string> developmentCards;
};

#endif // PLAYER_HPP
