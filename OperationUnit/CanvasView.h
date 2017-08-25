#pragma once
#include <QGraphicsView>
#include "CanvasScene.h"
#include <memory>
#include "OperationUnit/RelationSetDialog.h"
#include <QDebug>
#include <base/lang/not_null.h>

class AbstractItem;
class AbstractLine;

struct scoped_connection
{
    scoped_connection () = default;
    scoped_connection (QMetaObject::Connection conn)
        :data_ (std::move (conn))
    {

    }

    ~scoped_connection ()
    {
        if (data_)
        {
            QObject::disconnect (data_);
        }
    }

    QMetaObject::Connection data_;
};

class CanvasView : public QGraphicsView
{
    Q_OBJECT
signals:
    void itemPositionChanged();
    void selectionChanged(AbstractItem*);
public:
    template<typename ...ARGS>
    CanvasView(ARGS && ...args) : QGraphicsView(std::forward<ARGS> (args)...) { init(); }

    ~CanvasView() override;

    void relationSetDlgExec(const QVariant& oldData);
    qreal calculateMark() { return scene_->calculateMark(); }
    QVariant dump() const;
    bool load(const QVariant& data);

    QVariant cellMark(int col) const;
    QVariant cellRank(int col) const;
    QVariant cellType(int row) const;

    void operationUnitNameChanged(const QString& oldValue, const QString& newValue);
    void operationUnitTypeChanged(const QString& oldValue, const QString& newValue);
private:
    void init();
    void initConn();
    void generateChart (const QVariantMap &data);
    bool loadCanvas(const QVariantMap& data);
    bool loadRelationSetDlg(const QVariantMap& data);
    AbstractItem * makeItem (const QString & type);
    AbstractLine * makeLine (not_null<AbstractItem *> p1, not_null<AbstractItem*> p2, char type);
    void onSelectedChanged();
private:
    std::unique_ptr<CanvasScene> scene_;
    RelationSetDialog relationSetDlg_;

    QMetaObject::Connection selection_conn_;

};
