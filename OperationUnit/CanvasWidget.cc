#include "CanvasWidget.h"
#include "ui_canvaswidget.h"

CanvasWidget::CanvasWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CanvasWidget)
{
    ui->setupUi(this);

    initConn();
//    auto markWidget = std::make_unique<MarkWidget>();
//    auto ptr_markWidget = markWidget.get();
//    ui->dockWidget->setWidget(markWidget.release());
}

CanvasWidget::~CanvasWidget()
{
    delete ui;
}

void CanvasWidget::relationSetDlgExec()
{
    ui->canvasView->relationSetDlgExec();
}

QVariant CanvasWidget::dump() const
{
    return ui->canvasView->dump();
}

bool CanvasWidget::load(const QVariant& data)
{
    return ui->canvasView->load(data);
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
    auto markWidget = ui->markWidget;
    auto canvas = ui->canvasView;
    connect(ui->canvasView, &CanvasView::itemPositionChanged,
            [markWidget, canvas] () { const auto mark = canvas->calculateMark();
             markWidget->setMark(mark); }
           );

    connect(ui->canvasView, &CanvasView::selectionChanged,
            this, &CanvasWidget::selectionChanaged);
}

void CanvasWidget::selectionChanaged(AbstractItem *item)
{
    auto data = this->dump();
    ui->attributeWidget->selectedItemAttribute(item, data);
}
