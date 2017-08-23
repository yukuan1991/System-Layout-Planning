#include "OperationUnitRelationMain.h"
#include "ui_operationunitrelationmain.h"
#include <QMdiSubWindow>
#include <QFileDialog>
#include <QJsonDocument>
#include <base/io/file/file.hpp>
#include <base/utils/charset.hpp>
#include <QMessageBox>

OperationUnitRelationMain::OperationUnitRelationMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OperationUnitRelationMain)
{
    ui->setupUi(this);
    initConn();
    ui->mdiArea->setViewMode(QMdiArea::TabbedView);
    setWindowState(Qt::WindowMaximized);
}

OperationUnitRelationMain::~OperationUnitRelationMain()
{
    delete ui;
}

void OperationUnitRelationMain::initConn()
{
    connect(ui->rib, &OperationUnitRibbon::fileNew, this, &OperationUnitRelationMain::newBuild);
    connect(ui->rib, &OperationUnitRibbon::fileOpen, this, &OperationUnitRelationMain::fileOpen);

    connect(ui->rib, &OperationUnitRibbon::fileSave, this, &OperationUnitRelationMain::fileSave);
    connect(ui->rib, &OperationUnitRibbon::relationSetClicked,
            this, &OperationUnitRelationMain::relationSet);
}

void OperationUnitRelationMain::newBuild()
{
    auto w = createWindow();
}

void OperationUnitRelationMain::fileOpen()
{
    auto fileName = QFileDialog::getOpenFileName(this, "打开文件", ".", "System Layout Planning File(*.slp)");
    if(fileName.isEmpty())
    {
        return;
    }

    auto fileContent = file::read_all(::utf_to_sys(fileName.toStdString()).data());
    qDebug() << (*fileContent).data();

    if (!fileContent)
    {
        QMessageBox::information(this, "打开", "打开文件失败，请检查文件是否存在");
        return;
    }
    auto canvas = createWindow();
    const auto data = QJsonDocument::fromJson((*fileContent).data()).toVariant();
//    const auto data = QVariant((*fileContent).data());
    if (!canvas->load (data))
    {
        QMessageBox::information(this, "打开", "打开文件失败，文件已经损坏");
        return;
    }

    canvas->setWindowTitle(std::move (fileName));
}

void OperationUnitRelationMain::fileSave()
{
    auto canvas = activeWindow();
    if(canvas == nullptr)
    {
        return;
    }
    QString path;
    path = QFileDialog::getSaveFileName(this, "保存", ".", "System Layout Planning File(*.slp)");
    if(path.isEmpty())
    {
        return;
    }

    auto dumpCanvasData = canvas->dump();
    auto data = QJsonDocument::fromVariant(dumpCanvasData).toJson().toStdString();

    canvas->setWindowTitle(path);
    file::write_buffer(::utf_to_sys(path.toStdString()).data(), data.data());
}

void OperationUnitRelationMain::relationSet()
{
    auto w = activeWindow();
    if(w == nullptr)
    {
        return;
    }
    w->relationSetDlgExec();
}

not_null<CanvasWidget*> OperationUnitRelationMain::createWindow()
{
    auto canvas = std::make_unique<CanvasWidget> ();
    auto ptr_canvas = canvas.get();
    canvas->setAttribute(Qt::WA_DeleteOnClose);
    auto w = ui->mdiArea->addSubWindow (canvas.release());

    w->setWindowState(Qt::WindowMaximized);
    return ptr_canvas;
}

CanvasWidget *OperationUnitRelationMain::activeWindow()
{
    if(auto subWin = ui->mdiArea->activeSubWindow())
    {
        auto w = dynamic_cast<CanvasWidget*>(subWin->widget());

        return w;
    }
    else
    {
        return nullptr;
    }
}
