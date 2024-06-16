#ifndef BOARD_HPP
#define BOARD_HPP

#include <string>
#include <unordered_map>
#include <vector>

class Board
{
public:
    Board();

    bool isSettlementPlaceable(const std::string &location) const;
    bool isRoadPlaceable(const std::string &startLocation, const std::string &endLocation) const;
    void upgradeSettlementToCity(const std::string &location);
    std::string getHexagonByNumber(int number) const;
    std::string getResource(const std::string &hexagon) const;

private:
    std::unordered_map<std::string, std::string> hexagons;
    std::unordered_map<int, std::string> numberToHexagon;
};

#endif // BOARD_HPP
