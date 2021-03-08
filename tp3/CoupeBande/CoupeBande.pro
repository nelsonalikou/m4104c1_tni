# -----------------------------------------------------------
#  Project created by C:/Users/bigbo/OneDrive/Documents/cours_info_s4/M4104_TNI/tni/ImageToolbox/release\ImageToolbox lun. mars 8 2021
# -----------------------------------------------------------
QT -= core
QT -= gui
TARGET = CoupeBande
TEMPLATE = lib
CONFIG += release
DEFINES += COUPEBANDE_LIBRARY
win32:DEFINES += __WINDOWS__ _USE_MATH_DEFINES EXP_STL
win32:OBJECTS_DIR = ./objs
unix:OBJECTS_DIR = ./.objs
UI_DIR = ui
MOC_DIR = tmp
DESTDIR = release
INCLUDEPATH += ./ ui ../../../ImageToolbox
SOURCES += CoupeBande.cpp
HEADERS += CoupeBande.hpp
LIBS += -L../../../ImageToolbox/release -lplugin
