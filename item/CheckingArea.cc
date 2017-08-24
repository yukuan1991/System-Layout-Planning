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

    painter->drawRect(boundingRect());

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
