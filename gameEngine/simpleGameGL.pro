TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /usr/include/GL/ /usr/include/glew-2.1.0/ /usr/include/glm/ /usr/include/GLFW/

SOURCES += main.cpp

unix|win32: LIBS += -lglfw

unix|win32: LIBS += -lGLEW

unix|win32: LIBS += -lGLU

unix|win32: LIBS += -lglut

unix|win32: LIBS += -lGL
