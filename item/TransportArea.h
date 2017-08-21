﻿#pragma once
#include "item/AbstractItem.h"

class TransportArea : public AbstractItem
{
public:
    TransportArea(QGraphicsItem* parent = nullptr);
protected:
    void paint (QPainter * painter, const QStyleOptionGraphicsItem * option,
                QWidget * widget) override;
};

