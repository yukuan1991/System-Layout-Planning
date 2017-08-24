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
    painter->drawEllipse(boundingRect());

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
