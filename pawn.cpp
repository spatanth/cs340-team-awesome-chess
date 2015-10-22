#include "pawn.h"


// This class is not being used at the moment.
Pawn::Pawn()
{
    Pressed = false;
    //setFlag(ItemIsMovable);
}

QRectF Pawn::boundingRect() const
{
    return QRectF(0,0,30,30);
}

void Pawn::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush(Qt::blue);

    if(Pressed)
    {
        // brush.setColor(Qt::red);
    }
    else
    {
        brush.setColor(Qt::
                       green);
    }
    painter->fillRect(rec,brush);
    painter->drawRect(rec);
}

void Pawn::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Pressed = true;
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Pawn::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Pressed = false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
