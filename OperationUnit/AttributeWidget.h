#ifndef ATTRIBUTEWIDGET_H
#define ATTRIBUTEWIDGET_H

#include <QWidget>
#include "item/AbstractItem.h"

namespace Ui {
class AttributeWidget;
}

class AttributeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AttributeWidget(QWidget *parent = 0);
    ~AttributeWidget();

    void selectedItemAttribute(AbstractItem*, const QVariant&);
private:
    Ui::AttributeWidget *ui;
};

#endif // ATTRIBUTEWIDGET_H
