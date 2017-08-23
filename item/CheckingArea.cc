#include "CheckingArea.h"
#include <QPainter>

CheckingArea::CheckingArea(QGraphicsItem *parent)
    : AbstractItem (parent)
{

}

void CheckingArea::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED (option);
    Q_UNUSED (widget);
    painter->setBrush(Qt::blue);

    painter->drawRect(QRectF(0, 0, itemWidth, itemHeight));
}
