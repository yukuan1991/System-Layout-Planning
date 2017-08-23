#include "OperationUnitNameDelegate.h"
#include <QLineEdit>
#include <QComboBox>
#include "assert.h"
#include <QMessageBox>

OperationUnitNameDelegate::OperationUnitNameDelegate(QObject *parent)
    : QStyledItemDelegate (parent)
{

}

QWidget *OperationUnitNameDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    if(index.column() == 0)
    {
        return new QLineEdit(parent);
    }
    else if(index.column() == 1)
    {
        return new QComboBox(parent);
    }
    return nullptr;
}

void OperationUnitNameDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if(index.column() == 0)
    {
        auto edit = dynamic_cast<QLineEdit*>(editor); assert(edit);
        edit->setText(index.data().toString());
    }
    else if(index.column() == 1)
    {
        QStringList list;
        list << "" << "成型或处理加工区" << "装配区" << "与运输有关的作业区域" << "储存作业区域"
             << "停放或暂存区域" << "检验、测试区域" << "服务及辅助作业区域" << "办公室或规划面积";
        auto combo = dynamic_cast<QComboBox*>(editor); assert(combo);
        combo->addItems(list);
        combo->setCurrentText(index.data().toString());
    }
}

void OperationUnitNameDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if(index.column() == 0)
    {
        auto edit = dynamic_cast<QLineEdit*>(editor); assert(edit);
        auto row = model->rowCount();
        for(int i = 0; i < row; i++)
        {
            if(edit->text() == model->data(model->index(i, 0)))
            {
                QMessageBox::information(nullptr, "提示", "作业单位名称重复!");
                model->setData(index, {});
            }
        }
        model->setData(index, edit->text());
    }
    else if(index.column() == 1)
    {
        auto combo = dynamic_cast<QComboBox*>(editor); assert(combo);
        model->setData(index, combo->currentText());
    }
}
