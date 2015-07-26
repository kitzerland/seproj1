#-------------------------------------------------
#
# Project created by QtCreator 2015-07-18T16:48:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = SciCal2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    qcustomplot.cpp \
    xyz.cpp \
    graphwindow.cpp \
    savedialog.cpp \
    loaddialog.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    qcustomplot.h \
    xyz.h \
    graphwindow.h \
    fileio.h \
    savedialog.h \
    loaddialog.h \
    formulator.h

FORMS    += mainwindow.ui \
    dialog.ui \
    xyz.ui \
    graphwindow.ui \
    savedialog.ui \
    loaddialog.ui


RESOURCES += \
    calres.qrc
