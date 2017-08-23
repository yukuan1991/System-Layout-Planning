#include "AbstractLine.h"
#include <QDebug>
#include <assert.h>

AbstractLine::AbstractLine(not_null<AbstractItem *> start, not_null<AbstractItem *> stop)
{
    connect (start, &QGraphicsObject::xChanged, this, &AbstractLine::resetStart);
    connect (start, &QGraphicsObject::yChanged, this, &AbstractLine::resetStart);

    connect (stop, &QGraphicsObject::xChanged, this, &AbstractLine::resetStop);
    connect (stop, &QGraphicsObject::yChanged, this, &AbstractLine::resetStop);

    connect (start, &QObject::destroyed, this, &QObject::deleteLater);
    connect (stop, &QObject::destroyed, this, &QObject::deleteLater);

    start_ = start->sceneBoundingRect ().center ();
    stop_ = stop->sceneBoundingRect ().center ();

    setPos (0, 0);
    setZValue (- 100);
}

void AbstractLine::resetStart() noexcept
{
    const auto src = dynamic_cast<QGraphicsObject*> (sender ()); assert (src);
    start_ = src->sceneBoundingRect ().center ();
    update ();
}


void AbstractLine::resetStop() noexcept
{
    const auto src = dynamic_cast<QGraphicsObject*> (sender ()); assert (src);
    stop_ = src->sceneBoundingRect ().center ();
    update ();
}

AbstractLine::~AbstractLine ()
{

}

QRectF AbstractLine::verticalRect() const noexcept
{
    const auto line = QLineF (start_, stop_);
    const auto vLen = line.length ();
    const auto w = width ();

    return QRectF (- vLen / 2, - w / 2, vLen, w);
}

qreal AbstractLine::angle() const noexcept
{
    return QLineF (start_, stop_).angle ();
}
