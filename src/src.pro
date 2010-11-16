TEMPLATE = app
# Name of final binary file
TARGET = salarm
DEPENDPATH += .
INCLUDEPATH += . \
    scheduler \

QT += sql \
	phonon \


# Binary dir
DESTDIR = ../build/bin

# Objects dir
OBJECTS_DIR = ../build/obj

# Moc files dir
MOC_DIR = ../build/moc

# User-interface dir
UI_DIR = ../build/ui

# Resources dir
RCC_DIR = ../build/rcc


# Header files definition
HEADERS += mainwindow.h \
    optionsdialog.h \
    database.h \
    constants.h \
    scheduler/scheduler.h \
    scheduler/scheduledialog.h \
    scheduler/schedulermodel.h \
    scheduler/schedule.h \
    scheduler/schedulerproxymodel.h \
    scheduledelegate.h

# Sources definition
SOURCES += main.cpp \
    mainwindow.cpp \
    optionsdialog.cpp \
    database.cpp \
    scheduler/scheduler.cpp \
    scheduler/scheduledialog.cpp \
    scheduler/schedulermodel.cpp \
    scheduler/schedule.cpp \
    scheduler/schedulerproxymodel.cpp \
    scheduledelegate.cpp \
    constants.cpp

# Definition of application's forms
FORMS += ui/mainwindow.ui \
    ui/optionsdialog.ui \
    ui/scheduledialog.ui

# App resources
RESOURCES += ../icons.qrc

# List of translations
TRANSLATIONS += locale/salarm_cs_CZ.ts \
	locale/salarm_en_US.ts

include(../locale.pri)


unix {
	isEmpty(PREFIX):PREFIX = /usr
	BINDIR = $$PREFIX/bin
	DATADIR = $$PREFIX/share

	# Preprocesor variables
	DEFINES += DATADIR=\"$$DATADIR\"
	

    INSTALLS += target \
				desktop \
				icon \
				translations

	target.path = $$BINDIR
	desktop.path = $$DATADIR/applications
	desktop.files += ../$${TARGET}.desktop
	icon.path = $$DATADIR/icons/256x256/apps/$${TARGET}.png
	icon.fles += ../$${TARGET}.png

	translations.path = $$DATADIR/locale
	translations.files += ../build/bin/locale
}
