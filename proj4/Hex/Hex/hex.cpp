// Hex.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <time.h> 
#include "board.h"

// Return true if game is over.
bool humanMove(Board& board)
{
	int x(0);
	int y(0);

	// human / blue move
	cout << "Please enter your move: ";
	cin >> x >> y;
	while (!board.BlueMove(x, y))
	{
		cout << "Invalid move. Please enter your move: ";
		cin >> x >> y;
	}
	if (board.IsGameOver(Board::Color::BLUE, x, y))
	{
		system("cls");
		cout << "You Won!" << endl;
		cout << board;
		return true;
	}
	return false;
}

// Return true if game is over.
bool computerMove(Board& board)
{
	int x = rand() % board.Size();
	int y = rand() % board.Size();

	while (!board.RedMove(x, y))
	{
		x = rand() % board.Size();
		y = rand() % board.Size();
	}
	if (board.IsGameOver(Board::Color::RED, x, y))
	{
		system("cls");
		cout << "Computer Won!" << endl;
		cout << board;
		return true;
	}
	return false;
}

// Main game loop. this game pits a human player with a machine player.
// For simplicity, the human player wired into the main game loop as blue player.
// and play first move. 
// 
// The console UI denotse blue's positions with Xs and red's positions with Os.
//
// It is trivial to change the logic so that the user (i.e. the human player) can be blue or red player
// and play first or after the computer.
// 
//
int main()
{
	cout << "Welcome to the Hex game!" << endl;
	cout << "This game pits you, the human player, with the computer" << endl;
	cout << "You are the blue player, designated by X, play from left to right, and move first" << endl;
	cout << "Computer is the red player, designated by O, play from top to bottom" << endl;
	cout << endl;

	int boardSize;
	cout << "Enter to size of the hex board: ";
	cin >> boardSize;

	Board board(boardSize);
	srand((unsigned int)time(0));

	// play games repeatedly until gane is over
	while (true) {
		system("cls");
		cout << "Welcome to the Hex game!" << endl;
		cout << "You are the blue player, designated by X, play from left to right" << endl;
		cout << "To make a move enter a pair of number, x y, to specify your move position" << endl;
		cout << "Enter a space to separate row x and column y number" << endl;

		cout << board;

		// Human move 
		if (humanMove(board))
		{
			// return if game is over
			return 0;
		}

		// Computer/red move
		if (computerMove(board))
		{
			return 0;
		}
	}
	
}
