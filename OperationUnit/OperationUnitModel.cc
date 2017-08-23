#include "OperationUnitModel.h"
#include <QModelIndex>
#include <assert.h>

using std::find_if;
using std::end;
using std::begin;

constexpr std::array<std::pair<char, int>, 6> values
{{
    std::make_pair ('A', 4),
    std::make_pair ('E', 3),
    std::make_pair ('I', 2),
    std::make_pair ('O', 1),
    std::make_pair ('U', 0),
    std::make_pair ('X', -1),
}};

bool OperationUnitModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    const auto header = findVericalHeader(this, index);
    if (header == "排序" or header == "综合接近程度")
    {
        return false;
    }

    return QStandardItemModel::setData(mapIndex (index), value, role);
}

QVariant OperationUnitModel::data(const QModelIndex &index, int role) const
{
    const auto header = findVericalHeader(this, index);
    if ((header != "排序" and header != "综合接近程度") or role != Qt::DisplayRole)
    {
        return QStandardItemModel::data(mapIndex (index), role);
    }

    if (header == "综合接近程度")
    {
        const auto col = index.column();
        auto sum = 0;
        const auto rowCount = columnCount();
        for(int row = 0; row < rowCount; row++)
        {
            if(row == col)
            {
                continue;
            }

            const auto str = data(this->index(row, col),
                                  Qt::DisplayRole).toString().toStdString();
            if(str.empty())
            {
                return {};
            }

            const auto character = str.at(0);
            auto found = find_if(begin(values), end(values),
                                 [&](auto && c) { return c.first == character; });
            assert(found != end(values));
            sum += found->second;
        }
        return sum;
    }

    if(header == "排序")
    {
        const auto row = columnCount();
        struct info
        {
            int index;
            int value;
        };

        std::vector<info> results;
        for(int col = 0; col < columnCount(); col++)
        {
            bool is_ok = false;
            const auto sum = data(this->index(row, col), Qt::DisplayRole).toInt(&is_ok);
            results.emplace_back (info{.index = col, .value = sum});
        }

        std::sort (begin (results), end (results), [] (auto&&it1, auto&&it2)
        {
            return it1.value > it2.value;
        });

        const auto currentCol = index.column();

        if (currentCol < 0)
        {
            return {};
        }
        auto found = std::find_if (begin (results), end (results), [&] (auto && it)
        {
            return it.index == currentCol;
        });

        assert (found != end (results));

        return found - begin(results) + 1;
    }

    return {};
}

QString OperationUnitModel::findVericalHeader(const QStandardItemModel *model, const QModelIndex &index)
{
    return model->headerData(index.row(), Qt::Vertical, Qt::DisplayRole).toString();
}

QModelIndex OperationUnitModel::mapIndex(const QModelIndex &index)
{
    if (!index.isValid ())
    {
        return QModelIndex ();
    }

    const auto row = index.row ();
    const auto col = index.column ();

    if (row > col)
    {
        return index;
    }
    else
    {
        return index.model ()->index (col, row);
    }
}
