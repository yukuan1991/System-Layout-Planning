#-------------------------------------------------
#
# Project created by QtCreator 2017-08-10T13:49:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG -= c++11
QMAKE_CXXFLAGS += -std=c++1z

TARGET = Operation_unit_correlation_diagram
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cc\
    OperationUnitRelationMain.cc \
    OperationUnit/Ribbon.cc \
    OperationUnit/OperationUnitRelationAnalysis.cc \
    OperationUnit/OperationUnitRibbon.cc \
    OperationUnit/RelationSetDialog.cc \
    item/AbstractLine.cc \
    item/LineA.cc \
    item/LineO.cc \
    item/LineE.cc \
    item/LineI.cc \
    item/LineX.cc \
    item/AbstractItem.cc \
    item/AssemblyArea.cc \
    item/CheckingArea.cc \
    item/OfficeArea.cc \
    item/ProcessingZone.cc \
    item/ServiceArea.cc \
    item/StagingArea.cc \
    item/StorageArea.cc \
    item/TransportArea.cc \
    OperationUnit/CanvasScene.cc \
    OperationUnit/CanvasView.cc \
    OperationUnit/OperationUnitNameDelegate.cc \
    OperationUnit/OperationUnitDelegate.cc \
    OperationUnit/OperationUnitModel.cc \
    OperationUnit/CanvasWidget.cc \
    OperationUnit/MarkWidget.cc

HEADERS  += OperationUnitRelationMain.h \
    OperationUnit/Ribbon.h \
    OperationUnit/OperationUnitRelationAnalysis.h \
    OperationUnit/OperationUnitRibbon.h \
    OperationUnit/RelationSetDialog.h \
    item/AbstractLine.h \
    item/LineA.h \
    item/LineO.h \
    item/LineE.h \
    item/LineI.h \
    item/LineX.h \
    item/AbstractItem.h \
    item/AssemblyArea.h \
    item/CheckingArea.h \
    item/OfficeArea.h \
    item/ProcessingZone.h \
    item/ServiceArea.h \
    item/StagingArea.h \
    item/StorageArea.h \
    item/TransportArea.h \
    OperationUnit/CanvasScene.h \
    OperationUnit/CanvasView.h \
    OperationUnit/OperationUnitNameDelegate.h \
    OperationUnit/OperationUnitDelegate.h \
    OperationUnit/OperationUnitModel.h \
    OperationUnit/CanvasWidget.h \
    OperationUnit/MarkWidget.h

FORMS    += operationunitrelationmain.ui \
    OperationUnit/operationunitrelationanalysis.ui \
    OperationUnit/relationsetdialog.ui \
    OperationUnit/canvaswidget.ui \
    OperationUnit/markwidget.ui

LIBS += -lboost_filesystem
LIBS += -lboost_system
LIBS += -lboost_locale
LIBS += -liconv

DISTFILES +=
