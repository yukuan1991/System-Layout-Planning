#include "StagingArea.h"
#include <QPainter>

StagingArea::StagingArea(QGraphicsItem *parent)
    : AbstractItem (parent)
{

}

void StagingArea::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(QColor(255, 128, 0));

    int startAngle = 90 * 16;
    int spanAngle = -180 * 16;

    painter->drawChord(QRectF(0, 0, itemWidth, itemHeight), startAngle, spanAngle);
}
