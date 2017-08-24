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
signals:
    void operationUnitNameChanged(const QString& oldValue, const QString& newValue);
    void operationUnitTypeChanged(const QString& oldValue, const QString& newValue);
public:
    explicit AttributeWidget(QWidget *parent = 0);
    ~AttributeWidget();

    void selectedItemAttribute(AbstractItem*, const QVariant&);
private:
    void init();
    void initConn();
    void onButtonConfirmClicked();
    Ui::AttributeWidget *ui;
    QString name_;
    QString type_;

};

#endif // ATTRIBUTEWIDGET_H
