#-------------------------------------------------
#
# Project created by QtCreator 2018-06-08T14:19:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = haven-chart-editor
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += include/

SOURCES += \
    src/column_manager.cpp \
    src/editor_column.cpp \
    src/editor_layout.cpp \
    src/image_manager.cpp \
    src/main.cpp \
    src/main_window.cpp \
    src/ratio.cpp \
    src/kshchart.cpp

HEADERS += \
    include/column_manager.h \
    include/editor_column.h \
    include/editor_column_data.h \
    include/editor_layout.h \
    include/image_manager.h \
    include/main_window.h \
    include/ratio.h \
    include/kshchart.h

FORMS += \
    main_window.ui

RESOURCES += \
    resources.qrc
