#include "LineE.h"
#include <QPainter>

LineE::LineE(AbstractItem *start, AbstractItem *stop)
    : AbstractLine (start, stop)
{

}

qreal LineE::width() const noexcept
{
    return 20;
}

qreal LineE::mark() const noexcept
{
    return 3;
}

void LineE::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    const auto rect = verticalRect ();
    painter->setPen (QColor(255, 128, 0));
    painter->translate ((start () + stop ()) / 2);
    painter->rotate (- angle ());

    const auto topLeft = rect.topLeft ();
    const auto topRight = rect.topRight ();

    const auto bottomLeft = rect.bottomLeft ();
    const auto bottomRight = rect.bottomRight ();

    painter->drawLine (topLeft, topRight);

    painter->drawLine ((topLeft + bottomLeft) / 2, (topRight + bottomRight) / 2);

    painter->drawLine (bottomLeft, bottomRight);
}

QRectF LineE::boundingRect() const
{
    const auto rect = verticalRect ();
    const auto matrix = [angle = angle ()] () { QMatrix m; m.rotate (- angle); return m; } ();
    const auto polygon = QPolygonF (rect);
    const auto mapped_polygon = matrix.map(polygon);

    return {0, 0, 1000, 1000};
}
