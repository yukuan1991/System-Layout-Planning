#include "AbstractItem.h"
#include <QPainter>

AbstractItem::AbstractItem(QGraphicsItem *parent)
    : QGraphicsObject (parent)
{
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
}

QRectF AbstractItem::boundingRect() const
{
    return QRectF{0, 0, itemWidth, itemHeight};
}

void AbstractItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);
    painter->setPen(Qt::black);

}
