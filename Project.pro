#-------------------------------------------------
#
# Project created by QtCreator 2015-07-31T12:52:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Project
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    teacher.cpp \
    activity.cpp \
    staff.cpp \
    login.cpp \
    activityform.cpp \
    userform.cpp \
    mapping.cpp \
    activityreference.cpp

CONFIG += c++11

HEADERS  += mainwindow.h \
    employee.h \
    teacher.h \
    activity.h \
    staff.h \
    activityreference.h \
    login.h \
    userform.h \
    activityform.h \
    mapping.h \
    file_delegator.hpp

FORMS    += mainwindow.ui \
    login.ui \
    activityform.ui \
    userform.ui

RESOURCES += \
    resource.qrc
