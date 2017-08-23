#pragma once
#include "AbstractItem.h"


class ServiceArea : public AbstractItem
{
public:
    ServiceArea(QGraphicsItem *parent = nullptr);
protected:
    void paint (QPainter * painter, const QStyleOptionGraphicsItem * option,
                QWidget * widget) override;
};

