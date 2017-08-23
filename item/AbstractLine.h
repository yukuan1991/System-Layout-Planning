#pragma once
#include <QGraphicsObject>
#include "item/AbstractItem.h"
#include <base/lang/not_null.h>


class AbstractLine : public QGraphicsObject
{
    Q_OBJECT
public:
    AbstractLine(not_null<AbstractItem *> item1, not_null<AbstractItem *> item2);
    ~AbstractLine () override;

    QPointF start () const noexcept { return start_; }
    QPointF stop () const noexcept { return stop_; }
    QRectF verticalRect () const noexcept;
    qreal angle () const noexcept;
    virtual qreal width () const noexcept = 0;
    virtual qreal mark() const noexcept = 0;
private:
    void resetStart () noexcept;
    void resetStop () noexcept;

private:
    QPointF start_ = {0, 0}, stop_ = {0, 0};
};


