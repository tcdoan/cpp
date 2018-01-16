#include "ai.h"
#include <algorithm>
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand

using namespace std;

Ai::Ai(size_t n, size_t trials, const vector<Player>& players, const vector<vector<size_t>>& adj)
	: n(n), trials(trials), colors(players), adj(adj)
{
	srand((unsigned int)time(0));
}

std::pair<size_t, size_t> Ai::score(size_t hexToEval)
{
	vector<Player> players = colors;
	players[hexToEval] = Player::RED;

	vector<size_t> grays;
	for (size_t i = 0; i < n*n; i++)
	{
		if (Player::GRAY == players[i])
		{
			grays.push_back(i);
		}
	}

	// redWins = number of times red player win the gamne in simulation
	size_t redWins = 0;

	vector<Player> playerCopy = players;
	for (size_t i = 0; i < trials; i++)
	{
		// hold simulated players        
		random_shuffle(grays.begin(), grays.end());

		Player next = Player::BLUE;
		for (size_t id : grays)
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

bool Ai::isRedWon(const vector<Player>& playerCopy)
{
	// for dfs search
	vector<bool> marked(n*n, false);

	// Red wins when dfs connect from top edge to bottom edge.
	bool bottomEdgeVisited = false;

	// scan row 0
	for (size_t id = 0; id < n; id++)
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

void Ai::RedDfs(const vector<Player>& playerCopy, vector<bool>& marked, size_t node, bool& bottomEdgeVisited)
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

	vector<size_t> adjList = adj[node];
	for (size_t x : adjList)
	{
		if (!marked[x] && playerCopy[x] == Player::RED)
		{
			RedDfs(playerCopy, marked, x, bottomEdgeVisited);
		}
	}
}