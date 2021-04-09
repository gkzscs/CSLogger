QT += core
CONFIG += c++11 precompile_header
TEMPLATE = lib
TARGET = CSLogger

PRECOMPILED_HEADER += cslogger_stable.h

DEFINES += CSLOGGER_LIB


HEADERS +=  \
    Logger/cslogger_comdef.hpp  \
    Logger/cslogger.h \
    Markdown/markdown_comdef.hpp


SOURCES +=  \
    Logger/cslogger.cpp

