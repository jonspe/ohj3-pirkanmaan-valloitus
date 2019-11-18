TEMPLATE = subdirs

SUBDIRS += \
    CourseLib \
    Game \
    UnitTests

CONFIG += ordered

CourseLib.subdir = Course/CourseLib
Game.depends = CourseLib
UnitTests.depends = CourseLib
