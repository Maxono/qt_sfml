#-------------------------------------------------
#
# Project created by QtCreator 2016-01-14T15:34:17
#
#-------------------------------------------------

CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11
QT       += core gui
#QMAKE_CXXFLAGS += -save-temps
#QMAKE_CXXFLAGS_DEBUG += -E

CONFIG(release, debug|release): LIBS += -lsfml-graphics -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-graphics -lsfml-window -lsfml-system

LIBS += -lXtst -lX11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt_sfml
TEMPLATE = app


SOURCES += main.cpp\
				mainwindow.cpp \
		qsfmlcanvas.cpp \
		particlegenerator.cpp \
    canvas.cpp

HEADERS  += mainwindow.h \
		qsfmlcanvas.h \
		particlegenerator.h \
    canvas.h

FORMS    += mainwindow.ui
