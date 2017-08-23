#include "AssemblyArea.h"
#include <QPainter>

AssemblyArea::AssemblyArea(QGraphicsItem *parent)
    : AbstractItem (parent)
{

}

void AssemblyArea::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    AbstractItem::paint(painter, option, widget);

    painter->setBrush(Qt::red);
    const QRectF rect(0, 0, itemWidth, itemHeight);
    painter->drawEllipse(rect);

}
