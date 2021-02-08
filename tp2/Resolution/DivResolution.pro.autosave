# -----------------------------------------------------------
#  Project created by C:/Users/bigbo/OneDrive/Documents/cours_info_s4/M4104_TNI/tni/ImageToolbox/release\ImageToolbox lun. janv. 25 2021
# -----------------------------------------------------------
QT -= core
QT -= gui
TARGET = DivResolution
TEMPLATE = lib
CONFIG += release
DEFINES += DIVRESOLUTION_LIBRARY
win32:DEFINES += __WINDOWS__ _USE_MATH_DEFINES EXP_STL
win32:OBJECTS_DIR = ./objs
unix:OBJECTS_DIR = ./.objs
UI_DIR = ui
MOC_DIR = tmp
DESTDIR = release
INCLUDEPATH += ./ ui ../../../ImageToolbox
SOURCES += DivResolution.cpp
HEADERS += DivResolution.hpp
LIBS += -L../../../ImageToolbox/release -lplugin
