#include "scoreeval.h"
#include "player.h"
#include <algorithm>
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand

using std::random_shuffle;
using std::vector;

ScoreEval::ScoreEval(int n, int trials, const vector<Player>& players, const vector<vector<int>>& adj)
    : n(n), trials(trials), colors(players), adj(adj) { }

int myrandom (int i) { return std::rand()%i;}

double ScoreEval::score(int hexToEval)
{
    vector<Player> players = colors;
    players[hexToEval] = Player::RED;

    vector<int> grays;
    for (int i = 0; i < players.size(); i++)
    {
        if (Player::GRAY == players[i])
        {
            grays.push_back(i);
        }
    }

     // redWins = number of times red player win the gamne in simulation
    int redWins = 0;

    for (int i= 0; i < trials; i++)
    {
        srand((unsigned int)time(0));
        // hold simulated players
        vector<Player> playout = players;
        std::shuffle(grays.begin(), grays.end(), myrandom);

        Player player = Player::BLUE;
        for (int id : grays)
        {
            playout[id] = player;
            player = (player == Player::BLUE) ? Player::RED : Player::BLUE;
        }

        // check if Red player wins
        if (isRedWon(playout))
        {
            redWins += 1;
        }
    }

    double evalScore = (1.0 * redWins) /  trials;
    return evalScore;
}

bool ScoreEval::isRedWon(const vector<Player>& playout)
{
    // for dfs search
    vector<bool> marked(n*n, false);

    // Red wins when dfs connect from top edge to bottom edge.
    bool bottomEdgeVisited = false;

    // scan row 0
    for (int id = 0; id < n; id++)
    {
        if (playout[id] == Player::RED)
        {
            RedDfs(playout, marked, id, bottomEdgeVisited);
        }
    }

    if (bottomEdgeVisited)
    {
        return true;
    }
    return false;
}

void ScoreEval::RedDfs(const vector<Player>& playout, vector<bool>& marked, int node, bool& bottomEdgeVisited)
{
    if (bottomEdgeVisited)
    {
        return;
    }

    marked[node] = true;

    if (node / n == n - 1)
    {
        bottomEdgeVisited = true;
        return;
    }

    vector<int> adjList = adj[node];
    for (int x : adjList)
    {
        if (!marked[x] && playout[x] == Player::RED)
        {
            RedDfs(playout, marked, x, bottomEdgeVisited);
        }
    }
}

