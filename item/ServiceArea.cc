#include "ServiceArea.h"
#include <QPainter>

ServiceArea::ServiceArea(QGraphicsItem *parent)
    : AbstractItem (parent)
{

}

void ServiceArea::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(Qt::blue);

    int startAngle = 180 * 16;
    int spanAngle = -180 * 16;

    const auto topLeft = QPointF(boundingRect().topLeft().x(),
                                 boundingRect().topLeft().y() + itemHeight / 4);
    const auto bottomRight = QPointF(boundingRect().bottomRight().x(),
                                boundingRect().bottomRight().y() + itemHeight / 4);
    const auto paintRect = QRectF(topLeft, bottomRight);
    painter->drawChord(paintRect, startAngle, spanAngle);

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
