TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    parser.cpp \
    pagerank.cpp \
    matrix.cpp

HEADERS += \
    parser.h \
    pagerank.h \
    matrix.h

QMAKE_CXXFLAGS += -pedantic -Wall -Werror

INCLUDEPATH += /usr/local/Cellar/boost/1.55.0/include

LIBS += /usr/local/lib/libboost_regex-mt.a
