TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L"..\..\SFML-2.2\lib"

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window
CONFIG(debug  , debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window

INCLUDEPATH += "..\..\SFML-2.2\include"
DEPENDPATH += "..\..\SFML-2.2\include"

SOURCES += main.cpp \
    leftparen.cpp \
    number.cpp \
    operator.cpp \
    rightparen.cpp \
    token.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    constants.h \
    leftparen.h \
    number.h \
    operator.h \
    rightparen.h \
    token.h \
    stringtoken.h
