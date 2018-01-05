#ifndef BOARD_H
#define BOARD_H

#include <QVector>
#include "hex.h"
#include "player.h"
#include <vector>

using namespace std;

class Board
{
public:
    Board(size_t n);
    size_t Size() { return n*n; }
    void PlaceHexes();
    Hex* GetHex(size_t hexId);
    QVector<Hex*> GetHexes();
    bool BlueMove(size_t id);
    bool RedMove(size_t id);
    bool IsValidMove(size_t id);
    bool IsGameOver(Player player, size_t id);

private:
    size_t n;

    // adjacency list represent graph of the Hex board
    vector<vector<size_t>> adj;

    // colors represent which hex occupied by blue or red player
    vector<Player> players;
    QVector<Hex*> hexes;
    vector<size_t> MakeAdjList(size_t row, size_t col);
};

#endif // BOARD_H
