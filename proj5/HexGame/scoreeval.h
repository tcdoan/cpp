#ifndef SCOREEVAL_H
#define SCOREEVAL_H
#include <player.h>
#include <vector>

class ScoreEval
{
public:
    const int trialNum = 10000;
    ScoreEval(int id, std::vector<Player> players, std::vector<std::vector<int>>* adj);
    double score();
private:
    // hex to evaluate
    int hexId;

    // information about which player owns which hex
    std::vector<Player> colors;

    // graph representation of the hex board
    std::vector<std::vector<int>>* adj;

    // remaining gray hexes for score evaluation
    std::vector<int> grayHexes;
};

#endif // SCOREEVAL_H
