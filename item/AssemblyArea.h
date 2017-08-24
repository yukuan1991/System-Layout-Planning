#pragma once
#include "item/AbstractItem.h"


class AssemblyArea : public AbstractItem
{
public:
    AssemblyArea(QGraphicsItem *parent = nullptr);
protected:
    void paint (QPainter * painter, const QStyleOptionGraphicsItem * option,
                QWidget * widget) override;

};

