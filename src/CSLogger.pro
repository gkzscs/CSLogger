QT += core
CONFIG += c++11 precompile_header
TEMPLATE = lib
TARGET = CSLogger

PRECOMPILED_HEADER += cslogger_stable.h

DEFINES += CSLOGGER_LIB


HEADERS +=  \
    Logger/cslogger_comdef.hpp  \
    Logger/cslogger.h \
    Markdown/csmarkdownlogger.h \
    Markdown/markdown_comdef.hpp \
    cslogger_global.h


SOURCES +=  \
    Logger/cslogger.cpp \
    Markdown/csmarkdownlogger.cpp


OTHER_FILES = $$PWD/lib_x64/Desktop_Qt_5_12_6_MSVC2017_64bit/Debug/debug

win32 {
    inst.path = $$PWD/../bin
    inst.files = $${OTHER_FILES}/*.dll $${OTHER_FILES}/*.lib
    INSTALLS += inst
}
