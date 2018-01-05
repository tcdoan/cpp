#ifndef HEX_H
#define HEX_H

#include <QGraphicsPolygonItem>
#include "player.h"

class Board;

class Hex : public QGraphicsPolygonItem
{
public:
    Hex(Board* board, int id, QGraphicsItem* parent = NULL);
    void Place(Player player);
private:
    Board* board;
    int id;
    Player owner;
};

#endif // HEX_H
