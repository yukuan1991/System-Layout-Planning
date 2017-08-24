#include "MarkWidget.h"
#include "ui_markwidget.h"

#include <QDebug>

MarkWidget::MarkWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MarkWidget)
{
    ui->setupUi(this);
}

MarkWidget::~MarkWidget()
{
    delete ui;
}

void MarkWidget::setMark(qreal mark)
{
    ui->labelMark->setText(QString::number(mark));
}
