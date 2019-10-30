TEMPLATE = app
TARGET = TheGame

QT += core gui widgets

CONFIG += c++14

SOURCES += \
    Game/buildings/farm.cpp \
    Game/buildings/mine.cpp \
    Game/core/objectmanager.cpp \
    Game/tiles/animals.cpp \
    Game/tiles/evergreen.cpp \
    main.cpp \
    mapwindow.cc \
    Game/tiles/birch.cpp \
    Game/tiles/diamond.cpp \
    Game/tiles/grass.cpp \
    Game/tiles/lake.cpp \
    Game/tiles/ores.cpp \
    Game/tiles/sand.cpp \
    Game/tiles/stone.cpp \
    Game/buildings/city.cpp \
    Game/buildings/colony.cpp

HEADERS += \
    Game/buildings/farm.h \
    Game/buildings/mine.h \
    Game/core/objectmanager.h \
    Game/tiles/animals.h \
    Game/tiles/evergreen.h \
    mapwindow.hh \
    Game/core/resources.h \
    Game/tiles/birch.h \
    Game/tiles/diamond.h \
    Game/tiles/grass.h \
    Game/tiles/lake.h \
    Game/tiles/ores.h \
    Game/tiles/sand.h \
    Game/tiles/stone.h \
    Game/buildings/city.h \
    Game/buildings/colony.h

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
    mapwindow.ui
