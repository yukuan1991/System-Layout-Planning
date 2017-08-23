#pragma once
#include "Ribbon.h"

class OperationUnitRibbon : public Ribbon
{
    Q_OBJECT
signals:
    void relationSetClicked();
public:
    OperationUnitRibbon(QWidget* parent = nullptr);
private:
    void initConn();
private:
    RibbonTool* relationSet;
};

