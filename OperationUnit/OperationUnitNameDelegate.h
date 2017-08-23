#pragma once
#include <QStyledItemDelegate>

class OperationUnitNameDelegate : public QStyledItemDelegate
{
public:
    OperationUnitNameDelegate(QObject *parent = nullptr);
private:

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
};

