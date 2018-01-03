#ifndef HEX_H
#define HEX_H

#include <QGraphicsPolygonItem>
#include "player.h"

class Hex : public QGraphicsPolygonItem
{
public:
    Hex(QGraphicsItem* parent = NULL);

private:
    Player owner;
};

#endif // HEX_H
