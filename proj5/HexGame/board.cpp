#include "board.h"
#include "game.h"
#include <vector>
#include <time.h>

extern Game *game;

using std::vector;

Board::Board(int n) : n(n)
{
    adj = vector<vector<int>>(n*n);
    players = vector<Player>(n*n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // Create and store adjacency nodes
            adj[i*n + j] = MakeAdjList(i, j);
            players[i*n + j] = Player::GRAY;
        }
    }
}

QVector<Hex *> Board::GetHexes()
{
    return hexes;
}

Hex* Board::GetHex(int id)
{
    return hexes[id];
}

// return true if valid move is placed, false otherwise
void Board::BlueMove(int id)
{    
    if (!IsValidMove(id))
    {
        return;
    }

    players[id] = Player::BLUE;

    if (this->IsGameOver(Player::BLUE, id))
    {
        // DisplayGameOver();
        return;
    }
    this->RedMove();
}

void Board::RedMove()
{
    srand((unsigned int)time(0));
    currentPlayer = Player::RED;
    int x = rand() % this->Size();

    while (!this->IsValidMove(x))
    {
        x = rand() % this->Size();
    }

    players[x] = Player::RED;
    Hex* hex = GetHex(x);
    hex->Paint(Player::RED);

    if (this->IsGameOver(Player::RED, x))
    {
        // DisplayGameOver();
        return;
    }

    // move to the next player;
    currentPlayer = Player::BLUE;
}

bool Board::IsValidMove(int id)
{
    if (id >= Size() || id < 0)
    {
        return false;
    }

    if (players[id] != Player::GRAY)
    {
        return false;
    }
    return true;
}

bool Board::IsGameOver(Player player, int id)
{
    // for dfs search
    vector<bool> marked(Size(), false);

    // init beginNodeVisited and endNodeVisited with false
    bool beginNodeVisited = false;
    bool endNodeVisited = false;

    Dfs(marked, id, player, beginNodeVisited, endNodeVisited);

    if (beginNodeVisited && endNodeVisited)
    {
        game->Over = true;
        return true;
    }

    game->Over = false;
    return false;
}

// place hexes onto n by n board.
void Board::PlaceHexes()
{
    const int xmargin = 25;
    const int ymargin = 90;

    // row i, column j
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            Hex* hex = new Hex(this, i*n + j);
            hex->Paint(Player::GRAY);
            hex->setPos(xmargin + i * hex->boundingRect().width()/2 + j * hex->boundingRect().width(),
                        ymargin + i * hex->boundingRect().height() * 2.0/3.0);

            connect(hex, SIGNAL(clicked(int)), this, SLOT(BlueMove(int)));
            hexes.push_back(hex);
            game->scene->addItem(hex);
        }
    }
}

vector<int> Board::MakeAdjList(int row, int col)
{
    vector<int> adjList;
    if (row == 0)
    {
        if (col == 0)
        {
            adjList.push_back(row*n + col + 1);
            adjList.push_back((row+1)*n + col);
            return adjList;
        }
        else if (col == n-1)
        {
            adjList.push_back(row*n + col - 1);
            adjList.push_back((row + 1)*n + col -1);
            adjList.push_back((row + 1)*n + col);
            return adjList;
        }
        else
        {
            adjList.push_back(row*n + col - 1);
            adjList.push_back(row*n + col + 1);
            adjList.push_back((row + 1)*n + col - 1);
            adjList.push_back((row + 1)*n + col);
            return adjList;
        }
    }
    else if (row == n - 1)
    {
        if (col == 0)
        {
            adjList.push_back((row-1)*n + col);
            adjList.push_back((row - 1)*n + col+1);
            adjList.push_back(row*n + col + 1);
            return adjList;
        }
        else if (col == n - 1)
        {
            adjList.push_back((row - 1)*n + col);
            adjList.push_back(row*n + col - 1);
            return adjList;
        }
        else
        {
            adjList.push_back(row*n + col - 1);
            adjList.push_back(row*n + col + 1);
            adjList.push_back((row - 1)*n + col);
            adjList.push_back((row - 1)*n + col +1);
            return adjList;
        }
    }
    else
    {
        if (col == 0)
        {
            adjList.push_back((row - 1)*n + col);
            adjList.push_back((row - 1)*n + col + 1);
            adjList.push_back(row*n + col + 1);
            adjList.push_back((row + 1)*n + col);
            return adjList;
        }
        else if (col == n - 1)
        {
            adjList.push_back((row - 1)*n + col);
            adjList.push_back(row*n + col - 1);
            adjList.push_back((row + 1)*n + col -1);
            adjList.push_back((row + 1)*n + col);
            return adjList;
        }
        else
        {
            adjList.push_back((row - 1)*n + col);
            adjList.push_back((row - 1)*n + col + 1);
            adjList.push_back(row*n + col - 1);
            adjList.push_back(row*n + col + 1);
            adjList.push_back((row + 1)*n + col - 1);
            adjList.push_back((row + 1)*n + col);
            return adjList;
        }
    }
}

void Board::Dfs(vector<bool> marked, int node, Player player, bool& beginNodeVisited, bool& endNodeVisited)
{
    marked[node] = true;
    if (Player::BLUE == player && (node % n == 0))
    {
        beginNodeVisited = true;
    }

    if (Player::BLUE == player && (node % n == n - 1))
    {
        endNodeVisited = true;
    }

    if (Player::RED == player && (node / n == 0))
    {
        beginNodeVisited = true;
    }

    if (Player::RED == player && (node / n == n - 1))
    {
        endNodeVisited = true;
    }

    vector<int> adjList = adj[node];
    for (int x : adjList)
    {
        if (!marked[x] && players[x] == player)
        {
            Dfs(marked, x, player, beginNodeVisited, endNodeVisited);
        }
    }
}
