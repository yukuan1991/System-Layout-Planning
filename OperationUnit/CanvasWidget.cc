#include "CanvasWidget.h"
#include "ui_canvaswidget.h"

CanvasWidget::CanvasWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CanvasWidget)
{
    ui->setupUi(this);

    initConn();
}

CanvasWidget::~CanvasWidget()
{
    delete ui;
}

void CanvasWidget::relationSetDlgExec(const QVariant& oldData)
{
    ui->canvasView->relationSetDlgExec(oldData);
}

QVariant CanvasWidget::dump() const
{
    return ui->canvasView->dump();
}

bool CanvasWidget::load(const QVariant& data)
{
    if(!ui->canvasView->load(data))
    {
        return false;
    }
    emit markChanged();
    return true;
}

QVariant CanvasWidget::cellMark(int col) const
{
    return ui->canvasView->cellMark(col);
}

QVariant CanvasWidget::cellRank(int col) const
{
    return ui->canvasView->cellRank(col);
}

QVariant CanvasWidget::cellType(int row) const
{
    return ui->canvasView->cellType(row);
}

void CanvasWidget::initConn()
{

    connect(ui->canvasView, &CanvasView::itemPositionChanged, this, &CanvasWidget::markChanged);

    auto markWidget = ui->markWidget;
    auto canvas = ui->canvasView;
    connect(this, &CanvasWidget::markChanged,
            [markWidget, canvas] () { const auto mark = canvas->calculateMark();
             markWidget->setMark(mark); }
           );

    connect(ui->canvasView, &CanvasView::selectionChanged,
            this, &CanvasWidget::selectionChanaged);

    connect(ui->attributeWidget, &AttributeWidget::operationUnitNameChanged,
            this, &CanvasWidget::operationUnitNameChanged);
    connect(ui->attributeWidget, &AttributeWidget::operationUnitTypeChanged,
            this, &CanvasWidget::operationUnitTypeChanged);
}

void CanvasWidget::selectionChanaged(AbstractItem *item)
{
    auto data = this->dump();
    ui->attributeWidget->selectedItemAttribute(item, data);
}

void CanvasWidget::operationUnitNameChanged(const QString& oldValue, const QString& newValue)
{
    ui->canvasView->operationUnitNameChanged(oldValue, newValue);
}

void CanvasWidget::operationUnitTypeChanged(const QString& oldValue, const QString& newValue)
{
    ui->canvasView->operationUnitTypeChanged(oldValue, newValue);
}
