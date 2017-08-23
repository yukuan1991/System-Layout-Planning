#include "LineO.h"
#include <QPainter>

LineO::LineO(AbstractItem *start, AbstractItem *stop)
    : AbstractLine (start, stop)
{

}

qreal LineO::width() const noexcept
{
    return 10;
}

qreal LineO::mark() const noexcept
{
    return 1;
}

void LineO::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    const auto rect = verticalRect ();
    painter->setPen (Qt::blue);
    painter->translate ((start () + stop ()) / 2);
    painter->rotate (- angle ());

    const auto topLeft = rect.topLeft ();
    const auto topRight = rect.topRight ();

    const auto bottomLeft = rect.bottomLeft ();
    const auto bottomRight = rect.bottomRight ();

    painter->drawLine ((topLeft + bottomLeft) / 2, (topRight + bottomRight) / 2);
}

QRectF LineO::boundingRect() const
{
    const auto rect = verticalRect ();
    const auto matrix = [angle = angle ()] () { QMatrix m; m.rotate (- angle); return m; } ();
    const auto polygon = QPolygonF (rect);
    const auto mapped_polygon = matrix.map(polygon);

    return {0, 0, 1000, 1000};
}
