#pragma once
#include <QStandardItemModel>


class OperationUnitModel : public QStandardItemModel
{
public:
    template<typename ...ARGS>
    OperationUnitModel(ARGS && ...args) : QStandardItemModel(std::forward<ARGS> (args)...) {}

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QVariant data (const QModelIndex & index, int role = Qt::DisplayRole) const override;
    static QString findVericalHeader (const QStandardItemModel * model, const QModelIndex & index);
private:
    static QModelIndex mapIndex (const QModelIndex & index);
};

