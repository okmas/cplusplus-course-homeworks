TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

HEADERS += \
    filter_view.hpp \
    bind_last.hpp \
    bind_first.hpp

QMAKE_CXXFLAGS += -ansi -pedantic -Wall -Werror -Wextra
