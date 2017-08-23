#include "LineX.h"
#include <QPainter>

LineX::LineX(AbstractItem *start, AbstractItem *stop)
    : AbstractLine (start, stop)
{

}

qreal LineX::width() const noexcept
{
    return 10;
}

qreal LineX::mark() const noexcept
{
    return -1;
}

void LineX::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    const auto rect = verticalRect ();
    painter->setPen (Qt::black);
    painter->setPen (QPen(Qt::DashLine));
    painter->translate ((start () + stop ()) / 2);
    painter->rotate (- angle ());

    const auto topLeft = rect.topLeft ();
    const auto topRight = rect.topRight ();

    const auto bottomLeft = rect.bottomLeft ();
    const auto bottomRight = rect.bottomRight ();

    painter->drawLine ((topLeft + bottomLeft) / 2, (topRight + bottomRight) / 2);
}

QRectF LineX::boundingRect() const
{
    const auto rect = verticalRect ();
    const auto matrix = [angle = angle ()] () { QMatrix m; m.rotate (- angle); return m; } ();
    const auto polygon = QPolygonF (rect);
    const auto mapped_polygon = matrix.map(polygon);

    return {0, 0, 1000, 1000};
}
