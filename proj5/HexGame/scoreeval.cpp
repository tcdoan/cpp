#include "scoreeval.h"
#include "player.h"
#include <algorithm>
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand

using std::random_shuffle;
using std::vector;

ScoreEval::ScoreEval(const vector<Player>& players, const vector<vector<int>>& adj)
    : colors(players), adj(adj) { }

int myrandom (int i) { return std::rand()%i;}

double ScoreEval::score(int hexToEval)
{
    vector<Player> players = colors;
    players[hexToEval] = Player::RED;

    vector<int> grays;
    for (int i = 0; i < colors->size(); i++)
    {
        if (Player::GRAY == players[i])
        {
            grays.push_back(i);
        }
    }

     // redWins = number of times red player win the gamne in simulation
    int redWins = 0;

    for (int i= 0; i < trialNum; i++)
    {
        // hold simulated players
        vector<Player> playout = players;
        std::shuffle(grays.begin(), grays.end(), myrandom);

        Player player = Player::BLUE;
        for (int id : grays)
        {
            playout[id] = player;
            player = (player == Player::BLUE) ? Player::RED : Player::BLUE;
        }

        // check if isRedWon() won
    }
    return 1.0;
}
