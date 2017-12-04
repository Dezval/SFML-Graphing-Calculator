#########   Normal qmake Information      ####################

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp



##########   Library Information    ########################

#Note 1: In this project SFML is using dynamic linking
#Note 2: File paths are given relative path names.
#Note 3: You will need to place the dll files for whatever SFML library you are
# using in your program's build folder. i.e. sfml-graphics-d-2.dll. If these
# are not placed correctly, the program will build, but will crash when it is
# run.
#Note 4: If you are using SFML's sound library, you must copy
# libsndfile-1.dll and openal32.dll into your programs build directory


#This line tells qmake where to look for SFML header files
INCLUDEPATH += "../../sfml-2.2/include/"


#This line tells qmake where to look for SFML library files
LIBS += -L"../../sfml-2.2/lib/"


#This line tells qmake which SFML libraries to use (Debug/Release)
CONFIG(debug, debug|release): LIBS += -lsfml-graphics-d -lsfml-window-d -lsfml-audio-d -lsfml-network-d -lsfml-system-d
CONFIG(release, debug|release): LIBS += -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system
