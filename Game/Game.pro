TEMPLATE = app
TARGET = TheGame

QT += core gui widgets
QT += multimedia

CONFIG += c++14

SOURCES += \
    Game/buildings/advancedfarm.cpp \
    Game/buildings/advancedlumbercamp.cpp \
    Game/buildings/advancedmine.cpp \
    Game/buildings/diamondmine.cpp \
    Game/buildings/factory.cpp \
    Game/buildings/farm.cpp \
    Game/buildings/lumbercamp.cpp \
    Game/buildings/marketplace.cpp \
    Game/buildings/mine.cpp \
    Game/buildings/oremine.cpp \
    Game/buildings/university.cpp \
    Game/buildings/victorymonument.cpp \
    Game/core/marketplacetrader.cpp \
    Game/graphics/gamescene.cpp \
    Game/tiles/elevatedtilebase.cpp \
    Game/core/gameeventhandler.cpp \
    Game/core/mapgenerator.cpp \
    Game/core/objectmanager.cpp \
    Game/core/player.cpp \
    Game/graphics/gameview.cpp \
    Game/graphics/sprite.cpp \
    Game/tiles/animals.cpp \
    Game/tiles/evergreen.cpp \
    Game/workers/citizen.cpp \
    Game/workers/educatedcitizen.cpp \
    enddialog.cpp \
    main.cpp \
    mapwindow.cc \
    Game/tiles/birch.cpp \
    Game/tiles/diamond.cpp \
    Game/tiles/grass.cpp \
    Game/tiles/lake.cpp \
    Game/tiles/ores.cpp \
    Game/tiles/stone.cpp \
    Game/buildings/city.cpp \
    Game/buildings/colony.cpp \
    setupdialog.cpp

HEADERS += \
    Game/buildings/advancedfarm.h \
    Game/buildings/advancedlumbercamp.h \
    Game/buildings/advancedmine.h \
    Game/buildings/diamondmine.h \
    Game/buildings/factory.h \
    Game/buildings/farm.h \
    Game/buildings/lumbercamp.h \
    Game/buildings/marketplace.h \
    Game/buildings/mine.h \
    Game/buildings/oremine.h \
    Game/buildings/university.h \
    Game/buildings/victorymonument.h \
    Game/core/marketplacetrader.h \
    Game/core/objectmappings.h \
    Game/graphics/gamescene.h \
    Game/tiles/elevatedtilebase.h \
    Game/core/gameeventhandler.h \
    Game/core/mapgenerator.h \
    Game/core/objectmanager.h \
    Game/core/player.h \
    Game/graphics/gameview.h \
    Game/graphics/sprite.h \
    Game/tiles/animals.h \
    Game/tiles/evergreen.h \
    Game/workers/citizen.h \
    Game/workers/educatedcitizen.h \
    enddialog.h \
    mapwindow.hh \
    Game/core/resources.h \
    Game/tiles/birch.h \
    Game/tiles/diamond.h \
    Game/tiles/grass.h \
    Game/tiles/lake.h \
    Game/tiles/ores.h \
    Game/tiles/stone.h \
    Game/buildings/city.h \
    Game/buildings/colony.h \
    setupdialog.h

win32:CONFIG(release, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/release/ -lCourseLib
else:win32:CONFIG(debug, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/debug/ -lCourseLib
else:unix: LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/ -lCourseLib

INCLUDEPATH += \
    $$PWD/../Course/CourseLib

DEPENDPATH += \
    $$PWD/../Course/CourseLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/libCourseLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/libCourseLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/CourseLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/CourseLib.lib
else:unix: PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/libCourseLib.a

FORMS += \
    enddialog.ui \
    mapwindow.ui \
    setupdialog.ui

RESOURCES += \
    resources.qrc

