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
    database.h \
    constants.h \
    scheduler.h \
    scheduledialog.h \
    schedulermodel.h \
    schedule.h

# Sources definition
SOURCES += main.cpp \
    mainwindow.cpp \
    optionsdialog.cpp \
    database.cpp \
    constants.cpp \
    scheduler.cpp \
    scheduledialog.cpp \
    schedulermodel.cpp \
    schedule.cpp

# Definition of application's forms
FORMS += ui/mainwindow.ui \
    ui/optionsdialog.ui \
    ui/scheduledialog.ui

# App resources
RESOURCES += ../icons.qrc

# List of translations
TRANSLATIONS += locale/salarm_cs_CZ.ts
RESOURCES += 
