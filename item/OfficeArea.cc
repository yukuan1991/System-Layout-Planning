#include "OfficeArea.h"
#include <QPainter>

OfficeArea::OfficeArea(QGraphicsItem *parent)
    : AbstractItem (parent)
{

}

void OfficeArea::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(Qt::gray);

    static const QPointF points[7] = {
        QPointF(0, itemHeight / 3),
        QPointF(itemWidth / 2, 0),
        QPointF(itemWidth, itemHeight / 3),
        QPointF(itemWidth * 2 / 3, itemHeight / 3),
        QPointF(itemWidth * 2 / 3, itemHeight),
        QPointF(itemWidth / 3, itemHeight),
        QPointF(itemWidth / 3, itemHeight / 3)
    };

    painter->drawPolygon(points, 7);

    if(objectName().isEmpty())
    {
        return;
    }

    const auto width = painter->fontMetrics().width(objectName());
    const auto height = painter->fontMetrics().height();
    const auto center = boundingRect().center();
    auto rect = QRectF(center.x() - width / 2, center.y() - height / 2, width, height);

    painter->drawText(rect, Qt::AlignCenter, objectName());
}
