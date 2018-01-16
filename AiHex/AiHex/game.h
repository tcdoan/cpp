#pragma once
#include "entity.h"
#include <memory>

using namespace std;

class Game
{
public:
	State state;
	Game();
	void Reset();
	void Start();
	void BlueMove(size_t id);
	void RedMove();
private:
	size_t n;
	Font arialFont;
	Text textState;	
	RenderWindow window{ VideoMode(windowWidth, windowHeight), windowTitle };

	// adjacency list represent graph of the Hex board
	vector<vector<size_t>> adj;

	// players represent which hex occupied by blue or red player
	vector<Player> players;
	vector<unique_ptr<Hex>> hexes;

	size_t Size() { return n * n; }
	void PlaceHexes();
	void Draw();
	size_t GetClickedGrayHexId(Event event);
	bool IsValidMove(size_t id);
	bool IsGameOver(Player player, size_t id);

	// Use depth first search to check if game is over.
	void Dfs(vector<bool> marked, size_t node, Player player, bool& beginNodeVisited, bool& endNodeVisited);
	vector<size_t> MakeAdjList(size_t i, size_t j);
};
