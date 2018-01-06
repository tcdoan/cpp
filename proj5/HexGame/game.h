#ifndef GAME_H
#define GAME_H

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

    Player CurrentPlayer;
    bool Over;
public slots:
     void Start();
};

#endif // GAME_H
