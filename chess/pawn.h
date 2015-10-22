#ifndef PAWN_H
#define PAWN_H
#include <QPainter>
#include <QGraphicsItem>
#include <QDebug>


class Pawn : public QGraphicsItem
{
public:
    Pawn();


    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    bool Pressed;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

};

#endif // PAWN_H
