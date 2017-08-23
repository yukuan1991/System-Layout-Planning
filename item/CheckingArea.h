#pragma once
#include "item/AbstractItem.h"

class CheckingArea : public AbstractItem
{
public:
    CheckingArea(QGraphicsItem *parent = nullptr);
protected:
    void paint (QPainter * painter, const QStyleOptionGraphicsItem * option,
                QWidget * widget) override;
};

