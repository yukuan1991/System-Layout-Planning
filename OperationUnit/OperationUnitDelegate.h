#pragma once
#include <QStyledItemDelegate>

class OperationUnitDelegate : public QStyledItemDelegate
{
public:
    OperationUnitDelegate(QObject *parent = nullptr);
private:

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

};

