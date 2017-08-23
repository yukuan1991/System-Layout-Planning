#include "TransportArea.h"
#include <QPainter>

TransportArea::TransportArea(QGraphicsItem *parent)
    : AbstractItem (parent)
{

}

void TransportArea::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setBrush(QColor(255, 128, 0));

    static const QPointF points[7] = {
        QPointF(0, itemHeight / 3),
        QPointF(itemWidth * 2 / 3, itemHeight / 3),
        QPointF(itemWidth * 2 / 3, 0),
        QPointF(itemWidth, itemHeight / 2),
        QPointF(itemWidth * 2 / 3, itemHeight),
        QPointF(itemWidth * 2 / 3, itemHeight * 2 / 3),
        QPointF(0, itemHeight * 2 / 3)
    };

    painter->drawPolygon(points, 7);

}
