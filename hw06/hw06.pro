TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    client.cpp \
    virtualMachine.cpp \
    command.cpp

HEADERS += \
    queue.h \
    client.h \
    virtualMachine.h \
    command.h

