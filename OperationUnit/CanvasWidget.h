#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QWidget>
#include "item/AbstractItem.h"

namespace Ui {
class CanvasWidget;
}

class CanvasWidget : public QWidget
{
    Q_OBJECT
signals:
    void markChanged ();
public:
    explicit CanvasWidget(QWidget *parent = 0);
    ~CanvasWidget();

    void relationSetDlgExec(const QVariant& oldData);
    QVariant dump() const;
    bool load(const QVariant& data);
private:
    void initConn();
    void selectionChanaged(AbstractItem* item);
    void operationUnitNameChanged(const QString& oldValue, const QString& newValue);
    void operationUnitTypeChanged(const QString& oldValue, const QString& newValue);
private:
    Ui::CanvasWidget *ui;
};

#endif // CANVASWIDGET_H
