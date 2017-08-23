#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QWidget>

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
private:
    Ui::CanvasWidget *ui;
};

#endif // CANVASWIDGET_H
