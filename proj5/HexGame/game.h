#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "board.h"

#include <QGraphicsView>
#include <QGraphicsScene>


class Game : public QGraphicsView
{    
    Q_OBJECT
public:    
    Game(QWidget* parent=NULL);

    void DisplayMenu();

    // attributes
    QGraphicsScene* scene;
    Board* board;
    // The current player
     Player player;
     QString whosTurn;
public slots:
     void startGame();
};

#endif // GAME_H
