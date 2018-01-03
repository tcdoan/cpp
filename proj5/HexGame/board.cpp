#include "board.h"
#include "game.h"

extern Game *game;

Board::Board()
{

}

QVector<Hex *> Board::GetHexes()
{
    return hexes;
}

void Board::PlaceHexes(size_t n)
{
    const size_t xmargin = 25;
    const size_t ymargin = 90;

    // row i, column j
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            Hex* hex = new Hex();
            hex->setPos(xmargin + i * hex->boundingRect().width()/2 + j * hex->boundingRect().width(),
                        ymargin + i * hex->boundingRect().height() * 2.0/3.0);
            hexes.push_back(hex);
            game->scene->addItem(hex);
        }
    }
}

