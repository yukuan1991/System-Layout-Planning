#include "CanvasWidget.h"
#include "ui_canvaswidget.h"

CanvasWidget::CanvasWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CanvasWidget)
{
    ui->setupUi(this);

    auto markWidget = std::make_unique<MarkWidget>();
    auto ptr_markWidget = markWidget.get();
    auto canvas = ui->canvasView;
    connect(ui->canvasView, &CanvasView::itemPositionChanged,
            [ptr_markWidget, canvas] () { const auto mark = canvas->calculateMark();
             ptr_markWidget->setMark(mark); }
           );
    ui->dockWidget->setWidget(markWidget.release());
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
