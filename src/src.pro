QT += sql
CONFIG += qt

# Name of final binary file
TARGET = salarm
TEMPLATE = app
DESTDIR = ../build/bin
OBJECTS_DIR = ../build/obj
MOC_DIR = ../build/moc

# include ../dirs.pri
# Header files definition
HEADERS += mainwindow.h \
    optionsdialog.h \
    timer.h \
    database.h \
    constants.h \
    scheduler.h \
    schedule.h

# Sources definition
SOURCES += main.cpp \
    mainwindow.cpp \
    optionsdialog.cpp \
    timer.cpp \
    database.cpp \
    constants.cpp \
    scheduler.cpp \
    schedule.cpp

# Definition of application's forms
FORMS += ui/mainwindow.ui \
    ui/optionsdialog.ui

# App resources
RESOURCES += ../icons.qrc

# List of translations
TRANSLATIONS += locale/salarm_cs_CZ.ts
RESOURCES += 
