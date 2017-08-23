#include "LineI.h"
#include <QPainter>

LineI::LineI(AbstractItem *start, AbstractItem *stop)
    : AbstractLine (start, stop)
{

}

qreal LineI::width() const noexcept
{
    return 15;
}

qreal LineI::mark() const noexcept
{
    return 2;
}

void LineI::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    const auto rect = verticalRect ();
    painter->setPen (Qt::green);
    painter->translate ((start () + stop ()) / 2);
    painter->rotate (- angle ());

    const auto topLeft = rect.topLeft ();
    const auto topRight = rect.topRight ();

    const auto bottomLeft = rect.bottomLeft ();
    const auto bottomRight = rect.bottomRight ();

    painter->drawLine (topLeft, topRight);

    painter->drawLine (bottomLeft, bottomRight);
}

QRectF LineI::boundingRect() const
{
    const auto rect = verticalRect ();
    const auto matrix = [angle = angle ()] () { QMatrix m; m.rotate (- angle); return m; } ();
    const auto polygon = QPolygonF (rect);
    const auto mapped_polygon = matrix.map(polygon);

    return {0, 0, 1000, 1000};
}
