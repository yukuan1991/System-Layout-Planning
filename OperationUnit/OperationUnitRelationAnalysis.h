#ifndef OPERATIONUNITRELATIONANALYSIS_H
#define OPERATIONUNITRELATIONANALYSIS_H

#include <QWidget>
#include "OperationUnitDelegate.h"
#include "OperationUnitModel.h"

namespace Ui {
class OperationUnitRelationAnalysis;
}

class OperationUnitRelationAnalysis : public QWidget
{
    Q_OBJECT
public:
    explicit OperationUnitRelationAnalysis(QWidget *parent = 0);
    ~OperationUnitRelationAnalysis();

private:
    void setTable(int rows, int cols);
private:
    OperationUnitDelegate* delegate;
    OperationUnitModel* model;
private:
    Ui::OperationUnitRelationAnalysis *ui;
};

#endif // OPERATIONUNITRELATIONANALYSIS_H
