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

public:
    explicit CanvasWidget(QWidget *parent = 0);
    ~CanvasWidget();

    void relationSetDlgExec();
    QVariant dump() const;
    bool load(const QVariant& data);

    QVariant cellMark(int col) const;
    QVariant cellRank(int col) const;
    QVariant cellType(int row) const;
private:
    void initConn();
    void selectionChanaged(AbstractItem* item);
private:
    Ui::CanvasWidget *ui;
};

#endif // CANVASWIDGET_H
