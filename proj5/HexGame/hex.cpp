#include "hex.h"

Hex::Hex(QGraphicsItem* parent)
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
