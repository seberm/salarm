cmake_minimum_required(VERSION 2.6.0)
set(CMAKE_COLOR_MAKEFILE ON)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})

if (NOT DEFINED CMAKE_INSTALL_PREFIX)
	set(CMAKE_INSTALL_PREFIX /usr/local)
endif (NOT DEFINED CMAKE_INSTALL_PREFIX)

if (NOT DEFINED CMAKE_INSTALL_BINARY_DIR)
	set(INSTALL_BINARY_DIR ${CMAKE_INSTALL_PREFIX}/bin)
else (NOT DEFINED CMAKE_INSTALL_BINARY_DIR)
	set(INSTALL_BINARY_DIR ${CMAKE_INSTALL_BINARY_DIR})
endif (NOT DEFINED CMAKE_INSTALL_BINARY_DIR)

if (NOT DEFINED CMAKE_INSTALL_DATA_DIR)
   set(INSTALL_DATA_DIR ${CMAKE_INSTALL_PREFIX}/share)
else (NOT DEFINED CMAKE_INSTALL_DATA_DIR)
   set(INSTALL_DATA_DIR ${CMAKE_INSTALL_DATA_DIR})
endif (NOT DEFINED CMAKE_INSTALL_DATA_DIR)


set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)


add_subdirectory(salarm)
