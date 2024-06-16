#include "board.hpp"
#include <stdexcept>

Board::Board()
{
    // Initialize hexagons and their corresponding resources
    hexagons = {
        {"hex1", "wood"},
        {"hex2", "brick"},
        {"hex3", "wool"},
        {"hex4", "oat"},
        {"hex5", "iron"},
        // Add more hexagons as needed
    };

    // Initialize number to hexagon mapping
    numberToHexagon = {
        {2, "hex1"},
        {3, "hex2"},
        {4, "hex3"},
        {5, "hex4"},
        {6, "hex5"},
        // Add more number mappings as needed
    };
}

bool Board::isSettlementPlaceable(const std::string &location) const
{
    // Check if the location is a valid hexagon and whether a settlement can be placed there
    // Implement the logic based on game rules (e.g., no existing settlement or city)
    return hexagons.find(location) != hexagons.end();
}

bool Board::isRoadPlaceable(const std::string &startLocation, const std::string &endLocation) const
{
    // Check if the road can be placed between the start and end locations
    // Implement the logic based on game rules (e.g., adjacent hexagons)
    return hexagons.find(startLocation) != hexagons.end() && hexagons.find(endLocation) != hexagons.end();
}

void Board::upgradeSettlementToCity(const std::string &location)
{
    // Logic to upgrade a settlement to a city
    // Check if the location is a valid hexagon and there is an existing settlement
    auto it = hexagons.find(location);
    if (it != hexagons.end())
    {
        it->second = "city"; // Change the resource type to indicate a city
    }
    else
    {
        throw std::runtime_error("Invalid location for city upgrade.");
    }
}

std::string Board::getHexagonByNumber(int number) const
{
    // Return the hexagon corresponding to the rolled number
    auto it = numberToHexagon.find(number);
    if (it != numberToHexagon.end())
    {
        return it->second;
    }
    return "";
}

std::string Board::getResource(const std::string &hexagon) const
{
    // Return the resource type of the given hexagon
    auto it = hexagons.find(hexagon);
    if (it != hexagons.end())
    {
        return it->second;
    }
    return "";
}
