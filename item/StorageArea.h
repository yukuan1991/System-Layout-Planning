#pragma once
#include "AbstractItem.h"

class StorageArea : public AbstractItem
{
public:
    StorageArea(QGraphicsItem *parent = nullptr);
protected:
    void paint (QPainter * painter, const QStyleOptionGraphicsItem * option,
                QWidget * widget) override;
};

