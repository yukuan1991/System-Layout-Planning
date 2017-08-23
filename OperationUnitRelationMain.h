#ifndef OPERATIONUNITRELATIONMAIN_H
#define OPERATIONUNITRELATIONMAIN_H

#include <QWidget>
#include <base/lang/not_null.h>
#include "OperationUnit/CanvasView.h"
#include "OperationUnit/OperationUnitRelationAnalysis.h"
#include "OperationUnit/RelationSetDialog.h"
#include "OperationUnit/CanvasWidget.h"

namespace Ui {
class OperationUnitRelationMain;
}

class OperationUnitRelationMain : public QWidget
{
    Q_OBJECT

public:
    explicit OperationUnitRelationMain(QWidget *parent = 0);
    ~OperationUnitRelationMain();

private:
    void initConn();
private:
    void newBuild();
    void fileOpen();
    void fileSave();

    void relationSet();

    not_null<CanvasWidget*> createWindow();
    CanvasWidget* activeWindow();
private:
    Ui::OperationUnitRelationMain *ui;
//    RelationSetDialog relationSetDlg_;
};

#endif // OPERATIONUNITRELATIONMAIN_H
