#pragma once
#include <QGraphicsObject>


class AbstractItem : public QGraphicsObject
{
    Q_OBJECT
public:
    AbstractItem(QGraphicsItem *parent = nullptr);
protected:
    QRectF boundingRect () const override;
    void paint (QPainter * painter, const QStyleOptionGraphicsItem * option,
                QWidget * widget) override;
protected:
    static constexpr qreal itemWidth = 60;
    static constexpr qreal itemHeight = 60;
};

