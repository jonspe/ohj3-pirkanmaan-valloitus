QT       += testlib

QT += core gui widgets
TARGET = objectmanagertest

CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_objectmanagertest.cpp \
    ../../Course/CourseLib/buildings/buildingbase.cpp \
    ../../Course/CourseLib/core/basicresources.cpp \
    ../../Course/CourseLib/core/coordinate.cpp \
    ../../Course/CourseLib/core/gameobject.cpp \
    ../../Course/CourseLib/core/placeablegameobject.cpp \
    ../../Course/CourseLib/core/playerbase.cpp \
    ../../Course/CourseLib/tiles/tilebase.cpp \
    ../../Course/CourseLib/workers/basicworker.cpp \
    ../../Course/CourseLib/workers/workerbase.cpp \
    ../../Game/Game/buildings/city.cpp \
    ../../Game/Game/buildings/colony.cpp \
    ../../Game/Game/buildings/farm.cpp \
    ../../Game/Game/core/gameeventhandler.cpp \
    ../../Game/Game/core/objectmanager.cpp \
    ../../Game/Game/core/player.cpp \
    ../../Game/Game/graphics/gamescene.cpp \
    ../../Game/Game/graphics/gameview.cpp \
    ../../Game/Game/graphics/sprite.cpp \
    ../../Game/Game/tiles/birch.cpp \
    ../../Game/Game/tiles/elevatedtilebase.cpp \
    ../../Game/Game/tiles/evergreen.cpp \
    ../../Game/Game/workers/citizen.cpp \
    ../../Game/Game/workers/educatedcitizen.cpp \
    ../../Game/Game/core/marketplacetrader.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"


INCLUDEPATH += \
            ../../Course/CourseLib/ \
            ../../Game/

HEADERS += \
    ../../Course/CourseLib/buildings/buildingbase.h \
    ../../Course/CourseLib/core/basicresources.h \
    ../../Course/CourseLib/core/coordinate.h \
    ../../Course/CourseLib/core/gameobject.h \
    ../../Course/CourseLib/core/placeablegameobject.h \
    ../../Course/CourseLib/core/playerbase.h \
    ../../Course/CourseLib/core/resourcemaps.h \
    ../../Course/CourseLib/exceptions/baseexception.h \
    ../../Course/CourseLib/exceptions/illegalaction.h \
    ../../Course/CourseLib/exceptions/invalidpointer.h \
    ../../Course/CourseLib/exceptions/keyerror.h \
    ../../Course/CourseLib/exceptions/notenoughspace.h \
    ../../Course/CourseLib/exceptions/ownerconflict.h \
    ../../Course/CourseLib/interfaces/igameeventhandler.h \
    ../../Course/CourseLib/interfaces/iobjectmanager.h \
    ../../Course/CourseLib/tiles/tilebase.h \
    ../../Course/CourseLib/workers/basicworker.h \
    ../../Course/CourseLib/workers/workerbase.h \
    ../../Game/Game/buildings/city.h \
    ../../Game/Game/buildings/colony.h \
    ../../Game/Game/buildings/farm.h \
    ../../Game/Game/core/gameeventhandler.h \
    ../../Game/Game/core/objectmanager.h \
    ../../Game/Game/core/player.h \
    ../../Game/Game/core/resources.h \
    ../../Game/Game/graphics/gamescene.h \
    ../../Game/Game/graphics/gameview.h \
    ../../Game/Game/graphics/sprite.h \
    ../../Game/Game/tiles/birch.h \
    ../../Game/Game/tiles/elevatedtilebase.h \
    ../../Game/Game/tiles/evergreen.h \
    ../../Game/Game/workers/citizen.h \
    ../../Game/Game/workers/educatedcitizen.h \
    ../../Game/Game/core/marketplacetrader.h
