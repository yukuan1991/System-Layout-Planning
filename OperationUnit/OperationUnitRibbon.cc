#include "OperationUnitRibbon.h"
#include <base/lang/move.hpp>

OperationUnitRibbon::OperationUnitRibbon(QWidget *parent)
    : Ribbon(parent)
{
    {
        std::array<UiGroup, 1> edit;

        ButtonCell b;

        b.add("关系设置", QPixmap("png/关系设置.png"), relationSet);
        b.set_title("作业单位关系设置");

        edit[0] = ::move (b);
        setupTab(edit, "设置");
    }

    initConn();
}

void OperationUnitRibbon::initConn()
{
    connect(relationSet, &RibbonTool::clicked, this, &OperationUnitRibbon::relationSetClicked);
}
