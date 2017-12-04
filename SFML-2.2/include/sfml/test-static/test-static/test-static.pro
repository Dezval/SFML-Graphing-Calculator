#########   Normal qmake Information      ####################

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp



##########   Library Information    ########################

#Note 1: In this project SFML is using static linking
#Note 2: File paths are given relative path names.
#Note 3: If you are using SFML's sound library, you must copy
# libsndfile-1.dll and openal32.dll into your programs build directory


#This line needs to be here if linking to SFML statically.
DEFINES += SFML_STATIC


#This line tells qmake where to look for SFML header files
INCLUDEPATH += "../../sfml-2.2/include/"


#This line tells qmake where to look for SFML library files
LIBS += -L"../../sfml-2.2/lib/"


#This line tells qmake where to look for SFML's dependency library files
LIBS += -L"../../sfml-2.2/extlibs/libs-mingw/x86/"


#This line tells qmake which SFML libraries to use (Debug/Release)
CONFIG(debug, debug|release): LIBS += -lsfml-graphics-s-d -lsfml-window-s-d -lsfml-audio-s-d -lsfml-network-s-d -lsfml-system-s-d
CONFIG(release, debug|release): LIBS += -lsfml-graphics-s -lsfml-window-s -lsfml-audio-s -lsfml-network-s -lsfml-system-s


#This line tells qmake which SFML dependency libraries to use (same for Debug and Release)
LIBS += -lglew -lfreetype -ljpeg -lopengl32 -lgdi32 -lwinmm -lsndfile -lopenal32 -lws2_32
