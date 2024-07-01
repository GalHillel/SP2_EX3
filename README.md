# Catan Game

This project is a simulation of the popular board game Catan, implemented in C++ using object-oriented programming principles. The simulation includes basic game mechanics such as dice rolling, resource management, building settlements, cities, and roads, as well as handling the robber's movement and resource stealing.

## Game Rules Implemented

1. **Setup Phase:**
   - Players take turns placing settlements and roads on the board.
   - Each settlement gives the player initial resources based on adjacent terrain types.

2. **Resource Management:**
   - Players collect resources (wood, brick, wool, oat, iron) based on dice rolls.
   - Resources are used to build settlements, cities, and roads.

3. **Building:**
   - Settlements and roads can be placed on valid board locations.
   - Settlements can be upgraded to cities with additional resources.

4. **Robber Mechanism:**
   - Rolling a 7 activates the robber, allowing the active player to move it and steal resources from adjacent players.

## Class Hierarchy

### `Board`
- Manages the game board, including hexagon placement and adjacency.
- Methods handle placement of settlements, cities, roads, and robber movements.

### `Player`
- Represents a player in the game.
- Manages resources, settlements, cities, roads, victory points, and actions such as building and discarding.

### `Catan`
- Orchestrates the overall game flow, including turn management, dice rolling, and interaction between players and the board.

## Classes and Functionalities

### 1. Player
Represents a player in the game of Catan.

**Public Methods:**
- **Player(std::string name)**: Constructs a Player object with a given name.
- **void placeSettlement(const std::string &location, Board &board, bool isFirst)**: Places a settlement for the player on the board.
- **void placeRoad(const std::string &startLocation, const std::string &endLocation, Board &board, bool isFirst)**: Places a road for the player on the board.
- **void placeCity(const std::string &location, Board &board)**: Upgrades a settlement to a city.
- **void rollDice(Catan &game)**: Rolls the dice for the player's turn.
- **void trade(Player &other, const std::string &giveResource, const std::string &receiveResource, int giveAmount, int receiveAmount)**: Trades resources with another player.
- **void buyDevelopmentCard()**: Buys a development card.
- **void useDevelopmentCard(const std::string &card, Catan &game)**: Uses a development card.
- **void endTurn()**: Ends the player's turn.
- **void printResources() const**: Prints the player's resources.
- **void confirmTrade(Player &other, const std::string &giveResource, const std::string &receiveResource, int giveAmount, int receiveAmount)**: Confirms a trade with another player.
- **void addVictoryPoints(int points)**: Adds victory points to the player.
- **void subtractVictoryPoints(int points)**: Subtracts victory points from the player.
- **void addResource(const std::string &resource, int amount)**: Adds resources to the player.
- **int getVictoryPoints() const**: Gets the player's victory points.
- **int countTotalResources() const**: Counts the total resources the player has.
- **bool hasSettlement(const std::string &location, const Board &board)**: Checks if the player has a settlement at a given location.
- **bool hasCity(const std::string &location, const Board &board)**: Checks if the player has a city at a given location.
- **const std::unordered_map<std::string, int> &getResources() const**: Gets the player's resources.
- **const std::vector<std::string> &getDevelopmentCards() const**: Gets the player's development cards.
- **const std::vector<std::string> &getSettlements() const**: Gets the player's settlements.
- **const std::string &getName() const**: Gets the player's name.

### 2. Board
Represents the game board.

**Public Methods:**
- **void setRobberLocation(const std::string &location)**: Sets the location of the robber.
- **std::unordered_set<std::string> getPossibleSettlements() const**: Returns possible settlement locations.
- **std::vector<std::pair<std::string, std::string>> getPossibleRoads() const**: Returns possible road locations.
- **bool isSettlementPlaceable(const std::string &location, bool isFirst) const**: Checks if a settlement can be placed at a location.
- **std::string getHexagonByLocation(const std::string &location) const**: Returns the hexagon corresponding to a location.
- **std::string getResource(const std::string &hexagon) const**: Returns the resource of a hexagon.

### 3. Catan
Handles the game logic for Catan.

**Public Methods:**
- **Catan(Player &player1, Player &player2, Player &player3, Board &board)**: Constructs a Catan game instance with three players and a game board.
- **void play()**: Starts and plays the game.
- **Board &getBoard()**: Gets the game board.
- **void nextTurn()**: Advances the game to the next player's turn.
- **void chooseStartingLocations()**: Allows players to choose their starting locations at the beginning of the game.

## Dependencies
- Standard C++ libraries
- [Doctest](https://github.com/doctest/doctest) for unit testing

## Compilation and Execution
1. Ensure you have a C++ compiler installed (e.g., g++, clang++).
2. Clone the repository:
    ```sh
    git clone <repository_url>
    cd catan_game
    ```
3. Compile and run the project:
    ```sh
    make catan
    ```

## Unit Testing
Unit tests are written using the Doctest framework. To run the tests:
1. Ensure Doctest is included in your project.
2. Compile and run the test files:
    ```sh
    make check
    ```

## File Structure
- `main.cpp`: Entry point for the game simulation.
- `player.hpp`/`player.cpp`: Contains the Player class and its implementations.
- `board.hpp`/`board.cpp`: Contains the Board class and its implementations.
- `catan.hpp`/`catan.cpp`: Contains the Catan class and its implementations.
- `test_player.cpp`: Contains unit tests for the Player class.

## Libraries Used

- **Standard Library:** `<iostream>`, `<algorithm>`, `<stdexcept>`, `<ctime>`, `<cstdlib>`, `<random>`
   - Used for basic input/output, algorithmic operations, error handling, random number generation, and utility functions.
