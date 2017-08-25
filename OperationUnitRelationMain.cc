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
    setEnabled();
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
    connect(ui->rib, &OperationUnitRibbon::fileSaveAs, this, &OperationUnitRelationMain::fileSaveAs);
    connect(ui->rib, &OperationUnitRibbon::fileExit, this, &OperationUnitRelationMain::close);

    connect(ui->rib, &OperationUnitRibbon::relationSetClicked,
            this, &OperationUnitRelationMain::relationSet);
    connect(ui->mdiArea, &QMdiArea::subWindowActivated, this, &OperationUnitRelationMain::setEnabled);

}

void OperationUnitRelationMain::setEnabled()
{
    if(activeWindow())
    {
        emit ui->rib->subwindowActive(true);
    }
    else
    {
        emit ui->rib->subwindowActive(false);
    }
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

    if (!fileContent)
    {
        QMessageBox::information(this, "打开", "打开文件失败，请检查文件是否存在");
        return;
    }
    auto canvas = createWindow();
    const auto data = QJsonDocument::fromJson((*fileContent).data()).toVariant();

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

    QString path = canvas->windowTitle();
    if(path == "未命名")
    {
        path = QFileDialog::getSaveFileName(this, "保存", ".", "System Layout Planning File(*.slp)");
        if(path.isEmpty())
        {
            return;
        }

        canvas->setWindowTitle(path);
    }

    auto dumpCanvasData = canvas->dump();
    auto data = QJsonDocument::fromVariant(dumpCanvasData).toJson().toStdString();

    file::write_buffer(::utf_to_sys(path.toStdString()).data(), data.data());
}

void OperationUnitRelationMain::fileSaveAs()
{
    auto canvas = activeWindow();
    if(canvas == nullptr)
    {
        return;
    }

    auto path = QFileDialog::getSaveFileName(this, "另存为", ".", "System Layout Planning File(*.slp)");
    if(path.isEmpty())
    {
        return;
    }

    canvas->setWindowTitle(path);


    auto dumpCanvasData = canvas->dump();
    auto data = QJsonDocument::fromVariant(dumpCanvasData).toJson().toStdString();

    file::write_buffer(::utf_to_sys(path.toStdString()).data(), data.data());
}

void OperationUnitRelationMain::relationSet()
{
    auto w = activeWindow();
    if(w == nullptr)
    {
        return;
    }

    const auto data = w->dump();

    w->relationSetDlgExec(data);
}

not_null<CanvasWidget*> OperationUnitRelationMain::createWindow()
{
    const auto list = ui->mdiArea->subWindowList();

    auto canvas = std::make_unique<CanvasWidget> ();
    auto ptr_canvas = canvas.get();
    canvas->setAttribute(Qt::WA_DeleteOnClose);
    canvas->setWindowTitle("未命名");
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
