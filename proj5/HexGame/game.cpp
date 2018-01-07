#include "game.h"
#include "button.h"

Game::Game(QWidget *parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1024, 768);
    setWindowTitle("Hex Game - You vs Computer - You are blue and move first");

    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 1024, 768);
    setScene(scene);
}

void Game::DisplayMenu()
{
    QGraphicsTextItem* title = new QGraphicsTextItem(QString("Hex Game"));
    QFont font("comic sans", 50);
    title->setFont(font);
    int txPos = this->width()/2 - title->boundingRect().width()/2;
    int tyPos = 150;
    title->setPos(txPos,tyPos);
    scene->addItem(title);

    Button* playButton = new Button(QString("Play"));
    int bx = this->width()/2 - playButton->boundingRect().width()/2;
    int by = 275;
    playButton->setPos(bx, by);
    connect(playButton, SIGNAL(click()), this, SLOT(Start()));
    scene->addItem(playButton);

    Button* quitButton = new Button(QString("Quit"));
    int qx = this->width()/2 - quitButton->boundingRect().width()/2;
    int qy = 350;
    quitButton->setPos(qx, qy);
    connect(quitButton, SIGNAL(click()), this, SLOT(close()));
    scene->addItem(quitButton);
}

void Game::Start()
{
    Over = false;
    int n = 11;
    scene->clear();
    board = new Board(n);
    board->PlaceHexes();
    CurrentPlayer = Player::BLUE;
}
