#include "RelationSetDialog.h"
#include "ui_relationsetdialog.h"
#include "OperationUnitDelegate.h"
#include <memory>
#include <assert.h>
#include "OperationUnitModel.h"
#include <QMessageBox>
#include "OperationUnit/OperationUnitNameDelegate.h"
#include <base/lang/not_null.h>

#include <QDebug>

using std::make_unique;

RelationSetDialog::RelationSetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RelationSetDialog)
{
    ui->setupUi(this);

    ui->lineEdit->setValidator(new QIntValidator(2, 999, this));
    initConn();
}

RelationSetDialog::~RelationSetDialog()
{
    delete ui;
}

QVariant RelationSetDialog::dump() const
{
    if (model_ == null)
    {
        return {};
    }
    QVariantList relation;
    QVariantList mark;
    for (int col = 0; col < model_->columnCount (); col ++)
    {
        for (int row = col + 1; row < model_->columnCount (); row ++)
        {
            const auto cellData = model_->index (row, col).data (Qt::DisplayRole).toString ();
            if (cellData.isEmpty ())
            {
                return {};
            }

            relation.push_back (QString::number (row) + " " + QString::number (col) + " " + cellData);
        }
    }

    for (int col = 0; col < model_->columnCount (); col ++)
    {
        const auto row = model_->columnCount();
        const auto markData = model_->index(row, col).data(Qt::DisplayRole).toString();
        const auto sortData = model_->index(row + 1, col).data(Qt::DisplayRole).toString();
        mark.push_back(markData + " " + sortData);
    }

    if (nameModel_ == null)
    {
        return {};
    }

    QVariantList operationList;
    for (auto row = 0; row < nameModel_->rowCount (); row ++)
    {
        QVariantMap map;
        map ["name"] = nameModel_->data (nameModel_->index (row, 0), Qt::DisplayRole).toString ();
        map ["type"] = nameModel_->data (nameModel_->index (row, 1), Qt::DisplayRole).toString ();
        operationList.append (map);
    }

    QVariantMap totalMap;
    totalMap ["relation"] = relation;
    totalMap ["mark"] = mark;
    totalMap ["operations"] = operationList;

    return totalMap;
}

bool RelationSetDialog::load(const QVariantMap &data)
{
    const auto chartMap = data["charts"].toMap();
    const auto operation = chartMap["operations"].toList ();
    const auto relation = chartMap["relation"].toList ();

    const auto rows = operation.size();
    if(rows <= 0)
    {
        ui->tableWidget->setRowCount(0);
        ui->tableWidget->setColumnCount(0);
        ui->tableView->setModel(nullptr);
        ui->operationUnitForm->setModel(nullptr);
        ui->lineEdit->setText("");
        return false;
    }
    ui->lineEdit->setText(QString::number(rows));
    setTable(rows + 2, rows);

    for(int row = 0; row < rows; row++)
    {
        auto index = nameModel_->index(row, 0);
        const auto name = operation.at(row).toMap()["name"].toString();
        nameModel_->setData(index, name);
    }

    for(int row = 0; row < rows; row++)
    {
        auto index = nameModel_->index(row, 1);
        const auto type = operation.at(row).toMap()["type"].toString();
        nameModel_->setData(index, type);
    }

    for(auto it : relation)
    {
        const auto stringList = it.toString().split(" ");
        const auto relationRow = stringList.at(0).toInt();
        const auto relationCol = stringList.at(1).toInt();
        auto index = model_->index(relationRow, relationCol);
        model_->setData(index, stringList.at(2));
    }

    return true;
}

void RelationSetDialog::setTable(int rows, int cols)
{
    if (model_ == null)
        model_ = make_unique<OperationUnitModel> (rows, cols, this);
    if (delegate_ == null)
        delegate_ = make_unique<OperationUnitDelegate> (this);

    ui->tableView->setModel(model_.get ());
    ui->tableView->setItemDelegate(delegate_.get ());
    ui->tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->tableView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            auto item = std::make_unique<QStandardItem> ();
            if (i >= rows - 2)
            {
                item->setBackground (QColor (230, 230, 230));
            }
            model_->setItem(i, j, item.release ());
            model_->item(i, j)->setTextAlignment(Qt::AlignCenter);
        }
    }

    for(int row = 0; row < cols; row++)
    {
        int col = row;
        model_->item(row, col)->setEditable(false);
        model_->item(row, col)->setBackground(Qt::gray);
    }

    model_->setHeaderData(rows - 2, Qt::Vertical, "综合接近程度");
    model_->setHeaderData(rows - 1, Qt::Vertical, "排序");
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

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    if(nameModel_ == null)
    {
        nameModel_ = std::make_unique<QStandardItemModel> (cols, 2, this);
    }

    nameModel_->setHeaderData(0, Qt::Horizontal, "作业单位名称");
    nameModel_->setHeaderData(1, Qt::Horizontal, "作业单位工作性质");
    for(int i = 0; i < cols; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            auto item = std::make_unique<QStandardItem> ();
            nameModel_->setItem(i, j, item.release ());
            nameModel_->item(i, j)->setTextAlignment(Qt::AlignCenter);
        }
    }

    nameDelegate_ = std::make_unique<OperationUnitNameDelegate> ();

    ui->operationUnitForm->setModel(nameModel_.get());
    ui->operationUnitForm->setItemDelegate(nameDelegate_.get());
    ui->operationUnitForm->setColumnWidth(1, 150);
}

void RelationSetDialog::initConn()
{
    connect(ui->buttonModify, &QPushButton::clicked, this, &RelationSetDialog::buttonModify);

    connect(ui->buttonConfirm, &QPushButton::clicked, this, &RelationSetDialog::buttonConfirm);
    connect(ui->buttonCancel, &QPushButton::clicked, this, &RelationSetDialog::reject);

}

void RelationSetDialog::buttonConfirm()
{
    if(!checkDataPadding())
    {
        QMessageBox::information(this, "提示", "表中尚有数据未填充!");
    }
    else
    {
        accept();
    }
}

void RelationSetDialog::buttonModify()
{
    /// 很不优雅 QMessageBox::question
    if (model_ != null)
    {
        if (ui->tableWidget->rowCount() > 0)
        {
            auto ret = QMessageBox::question(this, "设置", "是否修改当前作业单位数？", "是", "否");
            constexpr auto yes = 0;
            if(ret != yes)
            {
                return;
            }
        }
    }

    const auto text = ui->lineEdit->text();
    bool isOk = false;
    const auto num = text.toInt(&isOk);

    if(isOk)
    {
        this->setTable(num + 2, num);
    }
}

bool RelationSetDialog::checkDataPadding()
{
    if(model_ == null)
    {
        return false;
    }

    ///判断综合关系表数据是否填充满
    const auto row = model_->rowCount();
    const auto col = model_->columnCount();

    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            if(i != j)
            {
                if(model_->data(model_->index(i, j)).toString().isEmpty())
                {
                    return false;
                }
            }
        }
    }

    ///判断作业单位信息表数据是否填充满
    const auto nameRow = nameModel_->rowCount();
    const auto nameCol = nameModel_->columnCount();
    for(int i = 0; i < nameRow; i++)
    {
        for(int j = 0; j < nameCol; j++)
        {
            if(nameModel_->data(nameModel_->index(i, j)).toString().isEmpty())
            {
                return false;
            }
        }
    }

    return true;
}

QVariant RelationSetDialog::cellMark(int col) const
{
    const auto row = model_->columnCount();
    const auto index = model_->index(row, col);
    return model_->data(index, Qt::DisplayRole);
}

QVariant RelationSetDialog::cellRank(int col) const
{
    const auto row = model_->columnCount() + 1;
    const auto index = model_->index(row, col);
    return model_->data(index, Qt::DisplayRole);
}

QVariant RelationSetDialog::cellType(int row) const
{
    const auto index = nameModel_->index(row, 1);
    return nameModel_->data(index, Qt::DisplayRole);
}

void RelationSetDialog::operationUnitNameChanged(const QString &oldValue, const QString &newValue)
{
    auto rows = nameModel_->rowCount();
    for(int row = 0; row < rows; row++)
    {
        const auto index = nameModel_->index(row, 0);
        const auto name = nameModel_->data(index, Qt::DisplayRole).toString();
        if(name == oldValue)
        {
            nameModel_->setData(index, newValue, Qt::DisplayRole);
        }
    }
}

