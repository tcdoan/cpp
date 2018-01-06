#ifndef HEX_H
#define HEX_H

#include <QGraphicsPolygonItem>
#include "player.h"
#include <QGraphicsItem>

class Board;

class Hex : public QObject, public QGraphicsPolygonItem
{
    Q_OBJECT
public:
    Hex(Board* board, int id, QGraphicsItem* parent = NULL);
    void Paint(Player player);

    // public events
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:
    clicked(int hexId);
private:
    Board* board;
    int id;
    Player owner;
};

#endif // HEX_H
