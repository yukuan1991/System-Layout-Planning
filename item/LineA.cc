#include "item/LineA.h"
#include <QPainter>
#include <QDebug>

LineA::LineA(AbstractItem *start, AbstractItem *stop)
    :AbstractLine (start, stop)
{

}

qreal LineA::width() const noexcept
{
    return 25;
}

qreal LineA::mark() const noexcept
{
    return 4;
}

void LineA::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    const auto rect = verticalRect ();
    painter->setPen (Qt::red);
    painter->translate ((start () + stop ()) / 2);
    painter->rotate (- angle ());

    const auto topLeft = rect.topLeft ();
    const auto topRight = rect.topRight ();

    const auto bottomLeft = rect.bottomLeft ();
    const auto bottomRight = rect.bottomRight ();

    painter->drawLine (topLeft, topRight);

    painter->drawLine ((2 * topLeft + bottomLeft) / 3, (2 * topRight + bottomRight) / 3);
    painter->drawLine ((topLeft + 2 * bottomLeft) / 3, (topRight + 2 * bottomRight) / 3);

    painter->drawLine (bottomLeft, bottomRight);
}

QRectF LineA::boundingRect() const
{
    const auto rect = verticalRect ();
    const auto matrix = [angle = angle ()] () { QMatrix m; m.rotate (- angle); return m; } ();
    const auto polygon = QPolygonF (rect);
    const auto mapped_polygon = matrix.map(polygon);

    return {0, 0, 1000, 1000};
}
