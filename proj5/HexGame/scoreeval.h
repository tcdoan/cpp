#ifndef SCOREEVAL_H
#define SCOREEVAL_H
#include <player.h>
#include <vector>

class ScoreEval
{
public:
    const int trialNum = 10000;
    ScoreEval(const std::vector<Player>& players, const std::vector<std::vector<int>>& adj);
    double score(int hexToEval);
private:
    // information about which player owns which hex
    std::vector<Player> colors;

    // graph representation of the hex board
    std::vector<std::vector<int>> adj;
};

#endif // SCOREEVAL_H
