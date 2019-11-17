QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    tst_objectmanagertest.cpp

INCLUDEPATH += \
    ../../Game \
    ../../Course/CourseLib \

DEPENDPATH += \
    ../../Game \
    ../../Course/CourseLib \

