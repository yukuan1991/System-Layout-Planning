#include "OperationUnitRelationAnalysis.h"
#include "ui_operationunitrelationanalysis.h"
#include <QInputDialog>

OperationUnitRelationAnalysis::OperationUnitRelationAnalysis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OperationUnitRelationAnalysis)
{
    ui->setupUi(this);
}

OperationUnitRelationAnalysis::~OperationUnitRelationAnalysis()
{
    delete ui;
}

void OperationUnitRelationAnalysis::setTable(int rows, int cols)
{
    model = new OperationUnitModel(rows, cols, this);
    delegate = new OperationUnitDelegate(this);

    ui->tableView->setModel(model);
    ui->tableView->setItemDelegate(delegate);

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            model->setItem(i, j, new QStandardItem);
            model->item(i, j)->setTextAlignment(Qt::AlignCenter);
        }
    }

    for(int row = 0; row < cols; row++)
    {
        int col = row;
        model->item(row, col)->setEditable(false);
        model->item(row, col)->setBackground(Qt::gray);
    }

    model->setHeaderData(rows - 2, Qt::Vertical, "综合接近程度");
    model->setHeaderData(rows - 1, Qt::Vertical, "排序");
    ui->tableView->verticalHeader()->setDefaultAlignment(Qt::AlignCenter);


    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount(6);
    QStringList horizontalHeader;
    horizontalHeader << "密切程度" << "分值";
    ui->tableWidget->setHorizontalHeaderLabels(horizontalHeader);
    QStringList verticalHeader;
    verticalHeader << "A" << "E" << "I" << "O" << "U" << "X";
    ui->tableWidget->setVerticalHeaderLabels(verticalHeader);
    for(int row = 0; row < 6; row++)
    {
        for(int col = 0; col < 2; col++)
        {
            ui->tableWidget->setItem(row, col, new QTableWidgetItem);
        }
    }
    ui->tableWidget->item(0, 0)->setData(Qt::DisplayRole, "绝对必要");
    ui->tableWidget->item(1, 0)->setData(Qt::DisplayRole, "特别重要");
    ui->tableWidget->item(2, 0)->setData(Qt::DisplayRole, "重要");
    ui->tableWidget->item(3, 0)->setData(Qt::DisplayRole, "一般");
    ui->tableWidget->item(4, 0)->setData(Qt::DisplayRole, "不重要");
    ui->tableWidget->item(5, 0)->setData(Qt::DisplayRole, "不希望");
    ui->tableWidget->item(0, 1)->setData(Qt::DisplayRole, 4);
    ui->tableWidget->item(1, 1)->setData(Qt::DisplayRole, 3);
    ui->tableWidget->item(2, 1)->setData(Qt::DisplayRole, 2);
    ui->tableWidget->item(3, 1)->setData(Qt::DisplayRole, 1);
    ui->tableWidget->item(4, 1)->setData(Qt::DisplayRole, 0);
    ui->tableWidget->item(5, 1)->setData(Qt::DisplayRole, -1);


    ui->operationUnitForm->setColumnCount(1);
    ui->operationUnitForm->setRowCount(cols);
    QStringList list;
    list << "作业单位名称";
    ui->operationUnitForm->setHorizontalHeaderLabels(list);
}


