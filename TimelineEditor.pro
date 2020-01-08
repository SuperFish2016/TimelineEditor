#-------------------------------------------------
#
# Project created by QtCreator 2020-01-06T09:45:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TimelineEditor
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

INCLUDEPATH += src/timelineutils
SOURCES += \
        src/main.cpp \
    src/timelinewidget.cpp \
    src/timelinetool/timelineabstracttool.cpp \
    src/timelinetool/timelinetooldelegate.cpp \
    src/timelinetool/timelinemovetool.cpp \
    src/timelinetool/timelineselectiontool.cpp \
    src/timelinegraphicsscene.cpp \
    src/timelineitem/timelinemovableitem.cpp \
    src/timelineitem/timelineitem.cpp \
    src/timelineitem/timelineframehandle.cpp \
    src/timelineutils/timelineutils.cpp \
    src/timelineutils/timelineicon.cpp \
    src/timelineutils/timelinetheme.cpp

HEADERS += \
    src/timelinewidget.h \
    src/timelinetool/timelineabstracttool.h \
    src/timelinetool/timelinetooldelegate.h \
    src/timelinetool/timelinemovetool.h \
    src/timelinetool/timelineselectiontool.h \
    src/timelinegraphicsscene.h \
    src/timelineitem/timelinemovableitem.h \
    src/timelineitem/timelineitem.h \
    src/timelineitem/timelineframehandle.h \
    src/timelineutils/timelineutils.h \
    src/timelineutils/timelineconstants.h \
    src/timelineutils/timelineicon.h \
    src/timelineutils/timelinetheme.h

FORMS +=


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src/timelineeditor.qrc
