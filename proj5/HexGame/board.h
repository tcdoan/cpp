#ifndef BOARD_H
#define BOARD_H

#include <QVector>
#include "hex.h"
#include "player.h"

using std::vector;

class Board : public QObject
{
    Q_OBJECT
public:
    Board(int n);
    int Size() { return n*n; }
    void PlaceHexes();    
    Hex* GetHex(int id);

    void RedMove();
    bool IsValidMove(int id);
    bool IsGameOver(Player player, int id);

public slots:
    void BlueMove(int id);

private:
    int n;

    // adjacency list represent graph of the Hex board
    std::vector<std::vector<int>> adj;

    // colors represent which hex occupied by blue or red player
    std::vector<Player> players;
    QVector<Hex*> hexes;
    void Dfs(vector<bool> marked, int node, Player player, bool& beginNodeVisited, bool& endNodeVisited);
    std::vector<int> MakeAdjList(int row, int col);
};

#endif // BOARD_H
