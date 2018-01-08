#ifndef SCOREEVAL_H
#define SCOREEVAL_H
#include <player.h>
#include <vector>

class ScoreEval
{
public:
    ScoreEval(int n, int trials, const std::vector<Player>& players, const std::vector<std::vector<int>>& adj);

    // maxScore sofar is used to cut off unnecessary trial runs
    int score(int hexToEval);
private:
    // board size
    int n;

    // number of simulation trials to evaluate and score
    int trials;

    // information about which player owns which hex
    std::vector<Player> colors;

    // graph representation of the hex board
    std::vector<std::vector<int>> adj;

    // check if red player won the simulated game.
    bool isRedWon(const std::vector<Player> &playerCopy);

    // use DFS search to check if red player won
    void RedDfs(const std::vector<Player>& playerCopy, std::vector<bool> &marked, int node, bool& bottomEdgeVisited);
};

#endif // SCOREEVAL_H
