#include "player.hpp"
#include "board.hpp"
#include <vector>

class Catan
{
public:
    Catan(Player &player1, Player &player2, Player &player3);

    void playGame();
    void nextTurn();
    void printStatus() const;
    void printWinner();
    void ChooseStartingPlayer();
    Board &getBoard();
    std::vector<Player> players;

private:
    size_t currentPlayerIndex;
    Board board;
};
