#pragma once

#include "constants.h"
using namespace std;

class Ai
{
public:
	Ai(size_t n, size_t trials, const vector<Player>& players, const vector<vector<size_t>>& adj);

	// maxScore sofar is used to cut off unnecessary trial runs
	pair<size_t, size_t> score(size_t hexToEval);
private:
	// board size
	size_t n;

	// number of simulation trials to evaluate and score
	size_t trials;

	// information about which player owns which hex
	vector<Player> colors;

	// graph representation of the hex board
	vector<vector<size_t>> adj;

	// check if red player won the simulated game.
	bool isRedWon(const vector<Player> &playerCopy);

	// use DFS search to check if red player won
	void RedDfs(const vector<Player>& playerCopy, vector<bool> &marked, size_t node, bool& bottomEdgeVisited);
};

