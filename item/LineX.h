#pragma once
#include "item/AbstractLine.h"

class LineX : public AbstractLine
{
public:
    LineX(AbstractItem * start, AbstractItem * stop);
protected:
    qreal width () const noexcept override;
    qreal mark() const noexcept override;
protected:
    void paint (QPainter * painter, const QStyleOptionGraphicsItem * option,
                QWidget * widget = null) override;
    QRectF boundingRect () const override;
};

