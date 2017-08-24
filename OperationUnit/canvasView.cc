#include "CanvasView.h"
#include <QInputDialog>
#include <QGraphicsScene>
#include "item/LineA.h"
#include "item/LineI.h"
#include "item/AssemblyArea.h"
#include "item/LineE.h"
#include "item/LineI.h"
#include "item/LineO.h"
#include "item/LineX.h"
#include "item/ProcessingZone.h"
#include "item/AssemblyArea.h"
#include "item/TransportArea.h"
#include "item/StorageArea.h"
#include "item/CheckingArea.h"
#include "item/OfficeArea.h"
#include "item/StagingArea.h"
#include "item/ServiceArea.h"
#include <QJsonDocument>
#include <boost/range/adaptor/indexed.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/algorithm/find_if.hpp>

#include <QDebug>

using namespace boost::adaptors;
using namespace boost;


CanvasView::~CanvasView()
{
	disconnect (selection_conn_);
}

void CanvasView::relationSetDlgExec()
{
    if (QDialog::Accepted != relationSetDlg_.exec ())
    {
		return;
	}

    const auto data = relationSetDlg_.dump ();

	generateChart (data.toMap ());
}

QVariant CanvasView::dump() const
{
	auto chartsMap = relationSetDlg_.dump().toMap();
	auto list = chartsMap["operations"].toList();

	auto items = this->items();
	QVariantList itemList;
	for(auto & it : items)
	{
		if(auto item = dynamic_cast<AbstractItem *>(it))
		{
			QVariantMap map;
			map["name"] = item->objectName();
			map["x"] = item->x();
			map["y"] = item->y();
			itemList.append(map);
		}
	}

	QVariantMap canvasMap;
	canvasMap["items"] = itemList;

	QVariantMap totalMap;
	totalMap["charts"] = chartsMap;
	totalMap["canvas"] = canvasMap;

	return totalMap;
}

bool CanvasView::load(const QVariant &data)
{
	const auto totalMap = data.toMap();
	if(!loadCanvas(totalMap))
	{
		return false;
	}


	if(!loadRelationSetDlg(totalMap))
	{
		return false;
	}

	return true;
}

void CanvasView::init()
{
    scene_ = std::make_unique<CanvasScene>(QRectF{0, 0, 1500, 1200});
    auto ptr_scene = scene_.get();
    this->setScene(ptr_scene);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

	setRenderHints (QPainter::Antialiasing);

	initConn();
}

void CanvasView::initConn()
{
	selection_conn_ = connect (scene_.get (), &CanvasScene::selectionChanged,
	                                                 this, &CanvasView::onSelectedChanged);


}

void CanvasView::generateChart(const QVariantMap & data)
{
	if(scene_->items().size() > 0)
	{
		const auto itemList = scene_->items();
		auto itemRng = itemList
		        | transformed([] (auto && c) { return dynamic_cast<AbstractItem *>(c); })
		        | filtered([] (auto && c) { return c != nullptr; });
		for(auto && item : itemRng)
		{
			item->deleteLater();
		}
		auto lineRng = itemList
		        | transformed([] (auto && c) { return dynamic_cast<AbstractLine *>(c); })
		        | filtered([] (auto && c) { return c != nullptr; });
		for(auto && line : lineRng)
		{
			line->deleteLater();
		}
	}

    const auto list = data ["operations"].toList ();
    const auto lines = data ["relation"].toList ();

    std::map<int, AbstractItem*> items;
	for (auto item : list | indexed ())
	{
		auto obj = makeItem (item.value ().toMap () ["type"].toString ());
		obj->setObjectName(item.value().toMap()["name"].toString());
		items [item.index ()] = obj;
	}

	for (auto & it : lines)
	{
		const auto stringlist = it.toString ().split (" ");
		assert (stringlist.size () == 3);
		makeLine (items[stringlist.at (0).toInt ()], items[stringlist.at (1).toInt ()], stringlist.at (2).toStdString ().at (0));
	}

	const auto viewList = this->items ();
	auto op = viewList
	        | transformed ([] (auto && c) { return dynamic_cast<AbstractItem *>(c); })
	        | filtered ([] (auto && c) { return c != null; });

	auto pos = scene_->effectiveRect().center();

	for(auto it : op)
	{
		it->setPos(pos);
	}

}

bool CanvasView::loadCanvas(const QVariantMap &data)
{
	const auto canvasMap = data["canvas"].toMap();
	const auto chartMap = data["charts"].toMap();

	const auto items = canvasMap ["items"].toList();

	const auto operation = chartMap["operations"].toList ();

	std::map<int, AbstractItem*> itemList;
	int i = 0;
	for (auto it : operation)
	{
		auto found = find_if(items, [&] (auto && c)
		{ return c.toMap()["name"].toString() == it.toMap()["name"].toString(); });
		if(found == items.end())
		{
			return false;
		}

		const auto x = found->toMap()["x"].toInt();
		const auto y = found->toMap()["y"].toInt();

		auto obj = makeItem(it.toMap()["type"].toString());
		obj->setObjectName(it.toMap()["name"].toString());
		obj->setPos(QPointF(x, y));
		itemList[i] = obj;
		i++;
	}

	const auto lines = chartMap["relation"].toList();
	for (auto & it : lines)
	{
		const auto stringlist = it.toString ().split (" ");
		assert (stringlist.size () == 3);
		makeLine (itemList[stringlist.at (0).toInt ()], itemList[stringlist.at (1).toInt ()], stringlist.at (2).toStdString ().at (0));
	}

	return true;
}

bool CanvasView::loadRelationSetDlg(const QVariantMap &data)
{
	return relationSetDlg_.load(data);
}

AbstractItem *CanvasView::makeItem(const QString &type)
{
    AbstractItem * item = null;
	if (type == "成型或处理加工区")
	{
		item = new ProcessingZone;
	}
	else if (type == "装配区")
	{
		item = new AssemblyArea;
	}
	else if (type == "与运输有关的作业区域")
	{
		item = new TransportArea;
	}
	else if (type == "储存作业区域")
	{
		item = new StorageArea;
	}
	else if (type == "停放或暂存区域")
	{
		item = new StagingArea;
	}
	else if (type == "检验、测试区域")
	{
		item = new CheckingArea;
	}
	else if ("服务及辅助作业区域" == type)
	{
		item = new ServiceArea;
	}
	else if ("办公室或规划面积" == type)
	{
		item = new OfficeArea;
	}
	else
	{
		assert (false);
	}
	connect(item, &AbstractItem::xChanged, this, &CanvasView::itemPositionChanged);
	connect(item, &AbstractItem::yChanged, this, &CanvasView::itemPositionChanged);

    scene ()->addItem (item);

    return item;
}

AbstractLine *CanvasView::makeLine(not_null<AbstractItem *> p1, not_null<AbstractItem *> p2, char type)
{
    AbstractLine * line = null;

    if (type == 'A')
    {
	line = new LineA (p1, p2);
    }
    else if (type == 'E')
    {
	line = new LineE (p1, p2);
    }
    else if (type == 'I')
    {
	line = new LineI (p1, p2);
    }
    else if (type == 'O')
    {
	line = new LineO (p1, p2);
    }
    else if (type == 'X')
    {
	line = new LineX (p1, p2);
    }

    if (line != null)
    {
	scene ()->addItem (line);
    }

	return line;
}

void CanvasView::onSelectedChanged()
{
	const auto items = scene_->selectedItems();
	QList<AbstractItem*> selectedItems;
	for(auto & it : items)
	{
		if(auto item = dynamic_cast<AbstractItem*>(it))
		{
			selectedItems.push_back(item);
		}
	}

	if(selectedItems.size() == 1)
	{
		emit selectionChanged(selectedItems.at(0));
	}
	else
	{
		emit selectionChanged(nullptr);
	}
}

void CanvasView::operationUnitNameChanged(const QString& oldValue, const QString& newValue)
{
	const auto itemList = items();
	for(auto & it : itemList)
	{
		if(auto item = dynamic_cast<AbstractItem*>(it))
		{
			if(oldValue == item->objectName())
			{
				item->setObjectName(newValue);
			}
		}
	}
	scene_->update();

	relationSetDlg_.operationUnitNameChanged(oldValue, newValue);
}

void CanvasView::operationUnitTypeChanged(const QString& oldValue, const QString& newValue)
{
	Q_UNUSED(oldValue);
	Q_UNUSED(newValue);
}

QVariant CanvasView::cellMark(int col) const
{
	return relationSetDlg_.cellMark(col);
}

QVariant CanvasView::cellRank(int col) const
{
	return relationSetDlg_.cellRank(col);
}

QVariant CanvasView::cellType(int row) const
{
	return relationSetDlg_.cellType(row);
}
