QT += sql
CONFIG += qt

# Name of final binary file
TARGET = salarm
TEMPLATE = app
DESTDIR = ../build/bin

OBJECTS_DIR = ../build/obj
MOC_DIR = ../build/moc
UI_DIR = ../build/ui
RCC_DIR = ../build/rcc

INCLUDEPATH += . \
    scheduler \


# Header files definition
HEADERS += mainwindow.h \
    optionsdialog.h \
    database.h \
    constants.h \
    scheduler/scheduler.h \
    scheduler/scheduledialog.h \
    scheduler/schedulermodel.h \
    scheduler/schedule.h \
    scheduler/schedulerproxymodel.h

# Sources definition
SOURCES += main.cpp \
    mainwindow.cpp \
    optionsdialog.cpp \
    database.cpp \
    scheduler/scheduler.cpp \
    scheduler/scheduledialog.cpp \
    scheduler/schedulermodel.cpp \
    scheduler/schedule.cpp \
    scheduler/schedulerproxymodel.cpp

# Definition of application's forms
FORMS += ui/mainwindow.ui \
    ui/optionsdialog.ui \
    ui/scheduledialog.ui

# App resources
RESOURCES += ../icons.qrc \
    ../sounds.qrc


# List of translations
TRANSLATIONS += locale/salarm_cs_CZ.ts \
	locale/salarm_en_US.ts

include(../locale.pri)

unix {
    INSTALLS += target
    target.path = $$BINDIR
    INSTALLS += translations
    translations.path = $$PKGDATADIR/locale
    translations.files += build/bin/locale
}
