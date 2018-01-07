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

Hex* Board::GetHex(int id)
{
    return hexes[id];
}

// return true if valid move is placed, false otherwise
void Board::BlueMove(int id)
{
    game->CurrentPlayer = Player::BLUE;
    if (!IsValidMove(id))
    {
        return;
    }

    players[id] = Player::BLUE;
    this->GetHex(id)->Paint(Player::BLUE);

    if (this->IsGameOver(Player::BLUE, id))
    {
        // DisplayGameOver();
        return;
    }
    this->RedMove();
}

void Board::RedMove()
{
    game->CurrentPlayer = Player::RED;
    srand((unsigned int)time(0));
    int x = rand() % this->Size();

    while (!this->IsValidMove(x))
    {
        x = rand() % this->Size();
    }

    players[x] = Player::RED;
    this->GetHex(x)->Paint(Player::RED);

    if (this->IsGameOver(Player::RED, x))
    {
        // DisplayGameOver();
        return;
    }

    // move to the next player;
    game->CurrentPlayer = Player::BLUE;
}


// place hexes onto board.
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

bool Board::IsValidMove(int id)
{
    if (id >= Size() || id < 0 || players[id] != Player::GRAY)
    {
        return false;
    }

    return true;
}

bool Board::IsGameOver(Player player, int id)
{
    // for dfs search
    vector<bool> marked(Size(), false);

    // Game over when dfs connect from one edge to another.
    bool edgeNode1 = false;
    bool edgeNode2 = false;

    Dfs(marked, id, player, edgeNode1, edgeNode2);

    if (edgeNode1 && edgeNode2)
    {
        game->Over = true;
        return game->Over;
    }

    game->Over = false;
    return game->Over;
}

// row i, column j
vector<int> Board::MakeAdjList(int i, int j)
{
    vector<int> adjList;

    if (i > 0)
    {
        adjList.push_back((i-1)*n + j);
        if (j < n-1) adjList.push_back((i-1)*n + j+1);
    }

    if (i < n - 1)
    {
        if (j > 0) adjList.push_back((i + 1)*n + j-1);
        adjList.push_back((i + 1)*n + j);
    }

    if (j > 0)
    {
        adjList.push_back(i*n + j-1);
    }

    if (j < n - 1)
    {
        adjList.push_back(i*n + j + 1);
    }

    return adjList;
}

void Board::Dfs(vector<bool> marked, int node, Player player, bool& beginNodeVisited, bool& endNodeVisited)
{
    marked[node] = true;
    if (Player::BLUE == player)
    {
        if (node % n == 0) beginNodeVisited = true;
        if (node % n == n - 1) endNodeVisited = true;
    } else if (Player::RED == player)
    {
        if (node / n == 0) beginNodeVisited = true;
        if (node / n == n - 1) endNodeVisited = true;
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
