#pragma once
#include "item/AbstractItem.h"


class ProcessingZone : public AbstractItem
{
public:
    ProcessingZone(QGraphicsItem *parent = nullptr);
protected:
    void paint (QPainter * painter, const QStyleOptionGraphicsItem * option,
                QWidget * widget) override;
};

