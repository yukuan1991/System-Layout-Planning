#include "AttributeWidget.h"
#include "ui_attributewidget.h"
#include <boost/range/algorithm/find_if.hpp>
#include <QDebug>

using namespace boost;
AttributeWidget::AttributeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AttributeWidget)
{
    ui->setupUi(this);
    QStringList stringList;
    stringList << "" << "成型或处理加工区" << "装配区" << "与运输有关的作业区域" << "储存作业区域"
         << "停放或暂存区域" << "检验、测试区域" << "服务及辅助作业区域" << "办公室或规划面积";
    ui->combo->addItems(stringList);
}

AttributeWidget::~AttributeWidget()
{
    delete ui;
}

void AttributeWidget::selectedItemAttribute(AbstractItem *item, const QVariant& data)
{
    qDebug() << "AttributeWidget::selectedItemAttribute";

    if(item == nullptr)
    {
        ui->name->setText("");
        ui->combo->setCurrentText("");
        ui->mark->setText("");
        ui->number->setText("");
        return;
    }

    const auto name = item->objectName();
    ui->name->setText(name);
    auto totalMap = data.toMap();
    const auto canvasMap = totalMap["canvas"].toMap();
    const auto chartMap = totalMap["charts"].toMap();

    const auto operation = chartMap["operations"].toList ();
    const auto mark = chartMap["mark"].toList();
    qDebug() << operation.size();


    auto found = find_if(operation, [&] (auto && c){ return c.toMap()["name"].toString() == name; });
    if(found == operation.end())
    {
        return;
    }
    const auto row = found - operation.begin();
    qDebug() << "row:" << row;
    const auto type = found->toMap()["type"].toString();
    const auto list = mark.at(row).toString().split(" ");
    qDebug() << "type" << type;
    qDebug() << list.at(0);
    qDebug() << list.at(1);

    ui->combo->setCurrentText(type);
    ui->mark->setText(list.at(0));
    ui->number->setText(list.at(1));
}
