#pragma once
#include "AbstractItem.h"

class OfficeArea : public AbstractItem
{
public:
    OfficeArea(QGraphicsItem *parent = nullptr);
protected:
    void paint (QPainter * painter, const QStyleOptionGraphicsItem * option,
                QWidget * widget) override;
};

