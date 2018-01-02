#pragma once
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

class Board
{
public:
	enum class Color
	{
		GRAY,
		BLUE,
		RED
	};
	Board(int n)
	{
		size = n;
		adj = vector<vector<int>>(size*size);
		colors = vector<Color>(size*size);
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				// Create and store adjacency nodes 
				adj[i*size + j] = MakeAdjList(i, j);
				colors[i*size + j] = Color::GRAY;
			}
		}
	}

	int Size()
	{
		return size;
	}

	// return true if valid move is executed, false otherwise
	bool BlueMove(int row, int column)
	{
		if (!IsValidMove(row, column))
		{
			return false;
		}
		colors[row*size + column] = Color::BLUE;
		return true;
	}

	// return true if valid move is executed, false otherwise
	bool RedMove(int row, int column)
	{
		if (!IsValidMove(row, column))
		{
			return false;
		}
		colors[row*size + column] = Color::RED;
		return true;
	}

	// game over when both begin_node(left / top most) and end_node(right / bottom most) visited
	bool IsGameOver(Color color, int row, int col)
	{

		// for dfs search
		vector<bool> marked(size*size, false);

		// init beginNodeVisited (left/top most) and endNodeVisited (right/bottom most) with false
		bool beginNodeVisited = false;
		bool endNodeVisited = false;
		int start_node = row * size + col;

		Dfs(marked, start_node, color, beginNodeVisited, endNodeVisited);

		if (beginNodeVisited && endNodeVisited)
		{
			return true;
		}

		return false;
	}

	bool IsValidMove(int row, int column)
	{
		if (row >= size || row < 0)
		{
			return false;
		}

		if (column >= size || column < 0)
		{
			return false;
		}

		if (colors[row*size + column] != Color::GRAY)
		{
			return false;
		}
		return true;
	}


	friend ostream& operator<<(ostream& out, Board& board);
private:
	int size;

	// adjacency list coresponding to graph representation of the Hex board
	vector<vector<int>> adj;

	// colors represent which cell occupied by blue or red player
	// unoccupied cell representaed by gray
	vector<Color> colors;

	// dfs search
	void Dfs(vector<bool>& marked, int node, Color color, bool& beginNodeVisited, bool& endNodeVisited)
	{
		marked[node] = true;
		if (Color::BLUE == color && (node % size == 0))
		{
			beginNodeVisited = true;
		}

		if (Color::BLUE == color && (node % size == size - 1))
		{
			endNodeVisited = true;
		}

		if (Color::RED == color && (node / size == 0))
		{
			beginNodeVisited = true;
		}

		if (Color::RED == color && (node / size == size - 1))
		{
			endNodeVisited = true;
		}

		vector<int> adjList = adj[node];
		for (int n : adjList)
		{
			if (!marked[n] && colors[n] == color)
			{
				Dfs(marked, n, color, beginNodeVisited, endNodeVisited);
			}
		}
	}

	vector<int> MakeAdjList(int row, int col)
	{
		vector<int> adjList;
		if (row == 0)
		{
			if (col == 0)
			{
				adjList.push_back(row*size + col + 1);
				adjList.push_back((row+1)*size + col);
				return adjList;
			}
			else if (col == size-1)
			{
				adjList.push_back(row*size + col - 1);
				adjList.push_back((row + 1)*size + col -1);
				adjList.push_back((row + 1)*size + col);
				return adjList;
			}
			else
			{
				adjList.push_back(row*size + col - 1);
				adjList.push_back(row*size + col + 1);
				adjList.push_back((row + 1)*size + col - 1);
				adjList.push_back((row + 1)*size + col);
				return adjList;
			}
		}
		else if (row == size - 1)
		{
			if (col == 0)
			{
				adjList.push_back((row-1)*size + col);
				adjList.push_back((row - 1)*size + col+1);
				adjList.push_back(row*size + col + 1);
				return adjList;
			}
			else if (col == size - 1)
			{
				adjList.push_back((row - 1)*size + col);
				adjList.push_back(row*size + col - 1);
				return adjList;
			}
			else
			{
				adjList.push_back(row*size + col - 1);
				adjList.push_back(row*size + col + 1);
				adjList.push_back((row - 1)*size + col);
				adjList.push_back((row - 1)*size + col +1);
				return adjList;
			}
		}
		else
		{
			if (col == 0)
			{
				adjList.push_back((row - 1)*size + col);
				adjList.push_back((row - 1)*size + col + 1);
				adjList.push_back(row*size + col + 1);
				adjList.push_back((row + 1)*size + col);
				return adjList;
			}
			else if (col == size - 1)
			{
				adjList.push_back((row - 1)*size + col);
				adjList.push_back(row*size + col - 1);
				adjList.push_back((row + 1)*size + col -1);
				adjList.push_back((row + 1)*size + col);
				return adjList;
			}
			else
			{
				adjList.push_back((row - 1)*size + col);
				adjList.push_back((row - 1)*size + col + 1);
				adjList.push_back(row*size + col - 1);
				adjList.push_back(row*size + col + 1);
				adjList.push_back((row + 1)*size + col - 1);
				adjList.push_back((row + 1)*size + col);
				return adjList;
			}
		}
	}
};

// print out hex board
ostream& operator<<(ostream& out, Board& board)
{
	for (int i = 0; i < board.size; i++) {

		for (int k = 0; k < i; k++) {
			out << "  ";
		}

		for (int j = 0; j < board.size; j++) {
			if (board.colors[i*board.size + j] == Board::Color::BLUE)
			{
				out << "X";
			} else if (board.colors[i*board.size + j] == Board::Color::RED)
			{
				out << "O";
			}
			else
			{
				out << ".";
			}

			if (j != board.size - 1) {
				out << " - ";
			}
		}
		out << endl;
		for (int k = 0; k < i; k++) {
			out << "  ";
		}

		if (i != board.size - 1) {
			for (int j = 0; j < board.size; j++) {
				out << " \\";
				if (j != board.size - 1) {
					out << " /";
				}
			}
			out << endl;
		}
	}
	out << endl;
	return out;
}
