TEMPLATE = app

# Name of final binary file
TARGET = salarm
DEPENDPATH += .
INCLUDEPATH += . \
    scheduler \

QT += sql \
	phonon \

# Release option is ignored if debug is also specified
CONFIG += release \
		debug


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
RESOURCES += resources/icons.qrc

# List of translations
TRANSLATIONS += translations/salarm_cs_CZ.ts \
	translations/salarm_en_US.ts




###
CODECFORTR = UTF-8 
CODECFORSRC = UTF-8

!isEmpty(TRANSLATIONS) {

	isEmpty(QMAKE_LRELEASE) {

		win32:QMAKE_LRELEASE = $$[QT_INSTALL_BINS]\lrelease.exe
		else:QMAKE_LRELEASE = $$[QT_INSTALL_BINS]/lrelease
	}

	TSQM.name = lrelease ${QMAKE_FILE_IN}
	TSQM.input = TRANSLATIONS
	TSQM.output = ../build/bin/translations/${QMAKE_FILE_BASE}.qm
	TSQM.commands = $$QMAKE_LRELEASE ${QMAKE_FILE_IN} -qm ../build/bin/translations/${QMAKE_FILE_BASE}.qm
	TSQM.CONFIG = no_link target_predeps
	QMAKE_EXTRA_COMPILERS += TSQM
	PRE_TARGETDEPS += compiler_TSQM_make_all
}



### UNIX ###
unix {
	
	isEmpty(INSTALL_PREFIX):INSTALL_PREFIX = ./installation
	BINDIR = $$INSTALL_PREFIX/bin
	DATADIR = $$INSTALL_PREFIX/share

	# Preprocesor variables
	DEFINES += DATADIR=\"$$DATADIR\"
	

	INSTALLS += target \
				desktop \
				translations \
				icon16 \
				icon32 \
				icon64 \
				icon128 \
				icon256

	target.path = $$BINDIR

	desktop.path = $$DATADIR/applications
	desktop.files += ../$${TARGET}.desktop

	translations.path = $$DATADIR/$${TARGET}/locales
	translations.files += ../build/bin/translations

	icon16.path = $$DATADIR/icons/hicolor/16x16/apps/$${TARGET}.png
	icon16.files += ../img/desktopIcons/16x16/$${TARGET}.png
	icon32.path = $$DATADIR/icons/hicolor/32x32/apps/$${TARGET}.png
	icon32.files += ../img/desktopIcons/32x32/$${TARGET}.png
	icon64.path = $$DATADIR/icons/hicolor/64x64/apps/$${TARGET}.png
	icon64.files += ../img/desktopIcons/64x64/$${TARGET}.png
	icon128.path = $$DATADIR/icons/hicolor/128x128/apps/$${TARGET}.png
	icon128.files += ../img/desktopIcons/128x128/$${TARGET}.png
	icon256.path = $$DATADIR/icons/hicolor/256x256/apps/$${TARGET}.png
	icon256.files += ../img/desktopIcons/256x256/$${TARGET}.png

}
