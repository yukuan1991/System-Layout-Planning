#include "ProcessingZone.h"
#include "QPainter"

ProcessingZone::ProcessingZone(QGraphicsItem *parent)
    : AbstractItem (parent)
{

}

void ProcessingZone::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    AbstractItem::paint(painter, option, widget);

    painter->setBrush(Qt::green);
    const QRectF rect(0, 0, itemWidth, itemHeight);
    painter->drawEllipse(rect);

}
