#include "scoreeval.h"
#include "player.h"
#include <algorithm>
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand

using std::random_shuffle;
using std::vector;

ScoreEval::ScoreEval(int n, int trials, const vector<Player>& players, const vector<vector<int>>& adj)
    : n(n), trials(trials), colors(players), adj(adj)
{
    srand((unsigned int)time(0));
}

std::pair<int, int> ScoreEval::score(int hexToEval)
{
    vector<Player> players = colors;
    players[hexToEval] = Player::RED;

    vector<int> grays;
    for (int i = 0; i < n*n; i++)
    {
        if (Player::GRAY == players[i])
        {
            grays.push_back(i);
        }
    }

     // redWins = number of times red player win the gamne in simulation
    int redWins = 0;

    vector<Player> playerCopy = players;
    for (int i= 0; i < trials; i++)
    {
        // hold simulated players        
        std::random_shuffle(grays.begin(), grays.end());

        Player next = Player::BLUE;
        for (int id : grays)
        {
            playerCopy[id] = next;
            next = (next == Player::BLUE) ? Player::RED : Player::BLUE;
        }

        // check if Red player wins
        if (isRedWon(playerCopy))
        {
            redWins += 1;
        }
    }

    return std::make_pair(hexToEval, redWins);
}

bool ScoreEval::isRedWon(const vector<Player>& playerCopy)
{
    // for dfs search
    vector<bool> marked(n*n, false);

    // Red wins when dfs connect from top edge to bottom edge.
    bool bottomEdgeVisited = false;

    // scan row 0
    for (int id = 0; id < n; id++)
    {
        if (playerCopy[id] == Player::RED)
        {
            RedDfs(playerCopy, marked, id, bottomEdgeVisited);
        }
        if (bottomEdgeVisited)
        {
            return true;
        }
    }

    return false;
}

void ScoreEval::RedDfs(const vector<Player>& playerCopy, vector<bool>& marked, int node, bool& bottomEdgeVisited)
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
        if (!marked[x] && playerCopy[x] == Player::RED)
        {
            RedDfs(playerCopy, marked, x, bottomEdgeVisited);
        }
    }
}

