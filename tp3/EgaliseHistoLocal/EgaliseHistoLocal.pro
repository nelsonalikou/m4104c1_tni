# -----------------------------------------------------------
#  Project created by C:/Users/bigbo/OneDrive/Documents/cours_info_s4/M4104_TNI/tni/ImageToolbox/release\ImageToolbox lun. févr. 15 2021
# -----------------------------------------------------------
QT -= core
QT -= gui
TARGET = EgaliseHistoLocal
TEMPLATE = lib
CONFIG += release
DEFINES += EGALISEHISTOLOCAL_LIBRARY
win32:DEFINES += __WINDOWS__ _USE_MATH_DEFINES EXP_STL
win32:OBJECTS_DIR = ./objs
unix:OBJECTS_DIR = ./.objs
UI_DIR = ui
MOC_DIR = tmp
DESTDIR = release
INCLUDEPATH += ./ ui ../../../ImageToolbox
SOURCES += EgaliseHistoLocal.cpp
HEADERS += EgaliseHistoLocal.hpp
LIBS += -L../../../ImageToolbox/release -lplugin
