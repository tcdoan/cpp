#include "scoreeval.h"
#include "player.h"
#include <algorithm>
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand

using std::random_shuffle;
using std::vector;

ScoreEval::ScoreEval(int id, vector<Player> players, vector<vector<int>>* adj)
    : hexId(id), colors(players), adj(adj)
{
    colors[hexId] = Player::RED;
}

int myrandom (int i) { return std::rand()%i;}

double ScoreEval::score()
{
    for (int i = 0; i < colors->size(); i++)
    {
        if (Player::GRAY == colors[i])
        {
            grayHexes.push_back(i);
        }
    }

    int redWons = 0;
    for (int i= 0; i < trialNum; i++)
    {
        vector<Player> players = colors;
        std::shuffle(grayHexes.begin(), grayHexes.end(), myrandom);

        Player player = Player::BLUE;
        for (int id : grayHexes)
        {
            players[id] = player;
            player = (player == Player::BLUE) ? Player::RED : Player::BLUE;
        }

        // check who won
    }
    return 1.0;
}
