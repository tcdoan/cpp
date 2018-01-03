#ifndef BOARD_H
#define BOARD_H

#include <QVector>
#include "hex.h"

class Board
{
public:
    Board();
    QVector<Hex*> GetHexes();
    void PlaceHexes(size_t n);
private:
    QVector<Hex*> hexes;
};

#endif // BOARD_H
