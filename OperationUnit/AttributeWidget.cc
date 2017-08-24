#include "AttributeWidget.h"
#include "ui_attributewidget.h"
#include <boost/range/algorithm/find_if.hpp>
#include <QDebug>

using namespace boost;

AttributeWidget::AttributeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AttributeWidget),
    name_(QString{}),
    type_(QString{})
{
    ui->setupUi(this);
    init();
}

AttributeWidget::~AttributeWidget()
{
    delete ui;
}

void AttributeWidget::selectedItemAttribute(AbstractItem *item, const QVariant& data)
{
    if(item == nullptr)
    {
        name_ = QString{};
        type_ = QString{};
        ui->name->setText(name_);
        ui->type->setText(type_);
        ui->mark->setText("");
        ui->number->setText("");
        return;
    }

    name_ = item->objectName();

    auto totalMap = data.toMap();
    const auto canvasMap = totalMap["canvas"].toMap();
    const auto chartMap = totalMap["charts"].toMap();

    const auto operation = chartMap["operations"].toList ();
    const auto mark = chartMap["mark"].toList();

    auto found = find_if(operation, [&] (auto && c){ return c.toMap()["name"].toString() == name_; });
    if(found == operation.end())
    {
        return;
    }
    const auto row = found - operation.begin();

    type_ = found->toMap()["type"].toString();
    const auto list = mark.at(row).toString().split(" ");

    ui->name->setText(name_);
    ui->type->setText(type_);
    ui->mark->setText(list.at(0));
    ui->number->setText(list.at(1));
}

void AttributeWidget::init()
{
    initConn();
}

void AttributeWidget::initConn()
{
    connect(ui->buttonConfirm, &QPushButton::clicked, this, &AttributeWidget::onButtonConfirmClicked);
}

void AttributeWidget::onButtonConfirmClicked()
{
    const auto name = ui->name->text();
    const auto type = ui->type->text();

    if(name != name_ or type != type_)
    {
        emit operationUnitNameChanged(name_, name);
        emit operationUnitTypeChanged(type_, type);

        name_ = name;
        type_ = type;
    }
}
