#pragma once
#include "item/AbstractItem.h"

class StagingArea : public AbstractItem
{
public:
    StagingArea(QGraphicsItem *parent = nullptr);
protected:
    void paint (QPainter * painter, const QStyleOptionGraphicsItem * option,
                QWidget * widget) override;
};

