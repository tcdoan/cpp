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
public slots:
    void BlueMove(int id);

private:
    int n;

    // adjacency list represent graph of the Hex board
    vector<vector<int>> adj;

    // players represent which hex occupied by blue or red player
    std::vector<Player> players;
    QVector<Hex*> hexes;
    bool IsValidMove(int id);
    bool IsGameOver(Player player, int id);

    // Use depth first search to check if game is over.
    void Dfs(vector<bool> marked, int node, Player player, bool& beginNodeVisited, bool& endNodeVisited);
    vector<int> MakeAdjList(int i, int j);
};

#endif // BOARD_H
