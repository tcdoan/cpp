#include "hex.h"
#include <QBrush>

Hex::Hex(Board* board, int id, QGraphicsItem* parent) : board(board), id(id)
{
    const int SCALE_FACTOR = 6;
    QVector<QPointF> hexPoints;
    hexPoints << QPointF(0, 4) << QPointF(5, 0) << QPointF(10, 4)
              << QPointF(10, 8) << QPointF(5, 12) << QPointF(0, 8);

    for (QPointF& p : hexPoints)
    {
        p *= SCALE_FACTOR;
    }

    QPolygonF hexagon(hexPoints);
    setPolygon(hexagon);
}

void Hex::Place(Player player)
{
    owner = player;

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);

    switch(owner)
    {
        case Player::BLUE:
            brush.setColor(Qt::blue);
            break;
        case Player::RED:
            brush.setColor(Qt::red);
            break;
        default:
            brush.setColor(Qt::gray);
    }
    setBrush(brush);
}
