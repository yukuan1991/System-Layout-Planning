#ifndef MARKWIDGET_H
#define MARKWIDGET_H

#include <QWidget>

namespace Ui {
class MarkWidget;
}

class MarkWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MarkWidget(QWidget *parent = 0);
    ~MarkWidget();

    void setMark(qreal mark);
private:
    Ui::MarkWidget *ui;
};

#endif // MARKWIDGET_H
