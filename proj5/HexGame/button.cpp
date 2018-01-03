#include "button.h"
#include <QBrush>

Button::Button(QString name, QGraphicsItem* parent ) : QGraphicsRectItem(parent)
{
    setRect(0, 0, 200, 50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    setBrush(brush);

    text = new QGraphicsTextItem(name, this);
    int xPos = rect().width()/2 -  text->boundingRect().width()/2;
    int yPos = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xPos, yPos);

    // for responding to hover events
    setAcceptHoverEvents(true);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit click();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    // change colot so cyan
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::cyan);
    setBrush(brush);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    // change colot so cyan
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    setBrush(brush);
}
