#include "StorageArea.h"
#include <QPainter>

StorageArea::StorageArea(QGraphicsItem *parent)
    : AbstractItem (parent)
{

}

void StorageArea::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(QColor(255, 128, 0));
    static const QPointF points[3] = {
        QPointF(0, 0),
        QPointF(itemWidth, 0),
        QPointF(itemWidth / 2, itemHeight)
    };

    painter->drawPolygon(points, 3);

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
