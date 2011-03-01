project(salarm)

set(SALARM_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SALARM_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_MODULE_PATH ${SALARM_SOURCE_DIR}/../cmake/modules ${CMAKE_MODULE_PATH})

set(SALARM_VERSION_MAJOR 0)
set(SALARM_VERSION_MINOR 40)
set(SALARM_VERSION_REVISION 0)
set(SALARM_VERSION ${SALARM_VERSION_MAJOR}.${SALARM_VERSION_MINOR}.${SALARM_VERSION_REVISION})

find_package(PkgConfig REQUIRED)
find_package(Qt4 4.5 REQUIRED)
find_package(Phonon REQUIRED)

set(QT_USE_QTMAIN 1)
set(QT_USE_QTSQL 1)
set(QT_USE_QTNETWORK 1)
set(QT_USE_PHONON 1)

include(${QT_USE_FILE})

include_directories(
		${SALARM_BINARY_DIR}
		${QT_INCLUDE_DIR}
		${PHONON_INCLUDES}
		${SALARM_SOURCE_DIR}
		"scheduler"
)

configure_file(${SALARM_SOURCE_DIR}/constants.h.cmake ${SALARM_BINARY_DIR}/constants.h)

set(salarm_HDRS
	mainwindow.h
	database.h
	keycatcher.h
	optionsdialog.h
	scheduledelegate.h
	settings.h
	smtp.h
	timeoutdialog.h
	scheduler/schedule.h
	scheduler/scheduledialog.h
	scheduler/scheduler.h
	scheduler/schedulermodel.h
	scheduler/schedulerproxymodel.h
)

set(salarm_SRCS
	main.cpp
	mainwindow.cpp
	database.cpp
	keycatcher.cpp
	optionsdialog.cpp
	scheduledelegate.cpp
	settings.cpp
	smtp.cpp
	timeoutdialog.cpp
	scheduler/schedule.cpp
	scheduler/scheduledialog.cpp
	scheduler/scheduler.cpp
	scheduler/schedulermodel.cpp
	scheduler/schedulerproxymodel.cpp
)

set(salarm_QUIS
	ui/mainwindow.ui
	ui/optionsdialog.ui
	ui/scheduledialog.ui
	ui/timeoutdialog.ui
)

set(salarm_RCCS
	resources/icons.qrc
)

qt4_wrap_ui(salarm_QUIS_HDRS ${salarm_QUIS})
qt4_wrap_cpp(salarm_QMOC_SRCS ${salarm_HDRS})
qt4_add_resources(salarm_RCCS_SRCS ${salarm_RCCS})

option(LANGUAGES "Using translations")
if (NOT DEFINED LANGS)
	if (NOT LANGS)
		set(LANGUAGES "")
	else (NOT LANGS)
		string(REGEX MATCHALL [a-zA-Z]+
				langs1 ${LANGS})
		set (LANGUAGES ${langs1} CACHE STRING "Using translations" FORCE)
	endif (NOT LANGS)
endif (NOT DEFINED LANGS)
message("Translations to build: ${LANGUAGES}")


foreach (LANGUAGE ${LANGUAGES})
	set(TS ${salarm_SOURCE_DIR}/locales/${LANGUAGE}.ts)
	set(QM ${salarm_SOURCE_DIR}/locales/${LANGUAGE}.qm)
	set(TRANSLATIONS ${TRANSLATIONS} ${TS})
	set(TRANSLATIONS_BINARY ${TRANSLATIONS} ${QM})
	add_custom_command(
		OUTPUT ${QM}
		COMMAND ${QT_LRELEASE_EXECUTABLE} ${TS}
		MAIN_DEPENDENCY ${TS})
endforeach()
	
add_custom_target(translations_qt
				COMMAND ${QT_LUPDATE_EXECUTABLE} ${HEADERS} ${SOURCES} -ts ${TRANSLATIONS})

add_custom_command(TARGET translations_qt
				COMMAND ${QT_LRELEASE_EXECUTABLE} ${TRANSLATIONS})


add_executable(salarm
			${salarm_SRCS}
			${salarm_RCCS_SRCS}
			${salarm_QUIS_HDRS}
			${salarm_QMOC_SRCS}
			${GUI_TYPE}
			${TRANSLATIONS_BINARY}
)

target_link_libraries(salarm
		      ${QT_LIBRARIES}
		      ${QT_QTSQL_LIBRARIES}
			  ${QT_PHONON_LIBRARIES}
)

install(TARGETS salarm
	RUNTIME DESTINATION ${INSTALL_BINARY_DIR}
	PERMISSIONS OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)

if(UNIX)

	install(FILES ../salarm.desktop
			DESTINATION ${INSTALL_DATA_DIR}/applications
	)

	install(FILES ../img/desktopICons/16x16/salarm.png
			DESTINATION ${INSTALL_DATA_DIR}/icons/hicolor/16x16/apps
	)

	install(FILES ../img/desktopICons/32x32/salarm.png
			DESTINATION ${INSTALL_DATA_DIR}/icons/hicolor/32x32/apps
	)

	install(FILES ../img/desktopICons/64x64/salarm.png
			DESTINATION ${INSTALL_DATA_DIR}/icons/hicolor/64x64/apps
	)

	install(FILES ../img/desktopICons/128x128/salarm.png
			DESTINATION ${INSTALL_DATA_DIR}/icons/hicolor/128x128/apps
	)

	install(FILES ../img/desktopICons/256x256/salarm.png
			DESTINATION ${INSTALL_DATA_DIR}/icons/hicolor/256x256/apps
	)
endif(UNIX)
