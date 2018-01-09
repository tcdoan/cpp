#ifndef GAME_H
#define GAME_H

#include "board.h"
#include <QGraphicsView>
#include <QGraphicsScene>

class Game : public QGraphicsView
{    
    Q_OBJECT
public:
    static const int trials = 20000;
    Game(QWidget* parent=NULL);
    void DisplayMenu();
    void DisplayGameStatus();
    void UpdateGameStatus(Player whosTurn);
    void DisplayGameOver(Player winner);

    // attributes
    QGraphicsScene* scene;
    Board* board;

    QGraphicsTextItem* GameStatus;

    bool HasPieRuleChance = true;
    int lastBlueHex = 0;
    Player CurrentPlayer = Player::BLUE;
    bool Over = false;

public slots:
     void Start();
};

#endif // GAME_H
