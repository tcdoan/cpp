#ifndef BUTTON_H
#define BUTTON_H

#include <QString>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsTextItem>

class Button : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Button(QString name, QGraphicsItem* parent = nullptr);

    // public events
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
signals:
    void click();

private:
    QGraphicsTextItem* text;
};

#endif // BUTTON_H
