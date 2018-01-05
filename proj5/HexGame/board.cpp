#include "board.h"
#include "game.h"
extern Game *game;

using namespace std;

Board::Board(size_t n) : n(n)
{
    adj = vector<vector<size_t>>(n*n);
    players = vector<Player>(n*n);
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
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

Hex* Board::GetHex(size_t id)
{
    return hexes[id];
}

// return true if valid move is placed, false otherwise
bool Board::BlueMove(size_t id)
{
    if (!IsValidMove(id))
    {
        return false;
    }

    players[id] = Player::BLUE;
    return true;
}

// return true if valid move is executed, false otherwise
bool Board::RedMove(size_t id)
{
    if (!IsValidMove(id))
    {
        return false;
    }
    players[id] = Player::RED;

    Hex* hex = GetHex(id);
    hex->Place(Player::RED);
    return true;
}

bool Board::IsValidMove(size_t id)
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

bool Board::IsGameOver(Player player, size_t id)
{
    return true;
}

// place hexes onto n by n board.
void Board::PlaceHexes()
{
    const size_t xmargin = 25;
    const size_t ymargin = 90;

    // row i, column j
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            Hex* hex = new Hex(this, i*n + j);
            hex->Place(Player::GRAY);
            hex->setPos(xmargin + i * hex->boundingRect().width()/2 + j * hex->boundingRect().width(),
                        ymargin + i * hex->boundingRect().height() * 2.0/3.0);
            hexes.push_back(hex);
            game->scene->addItem(hex);
        }
    }
}

vector<size_t> Board::MakeAdjList(size_t row, size_t col)
{
    vector<size_t> adjList;
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
