cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_PREFIX_PATH $ENV{HOME}/Qt/5.5/gcc_64)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

project( main )

include_directories("source")
file(GLOB_RECURSE SOURCES "source/*.cpp")

add_executable( signLanguage ${SOURCES} )

# Libraries

# Leap SDK
include_directories("$ENV{LEAP_SDK}/include")
link_directories("$ENV{LEAP_SDK}/lib/x64")

if(UNIX)
	if(NOT APPLE)
		target_link_libraries( signLanguage "$ENV{LEAP_SDK}/lib/x64/libLeap.so" )
	endif(NOT APPLE)
endif(UNIX)

if(WIN32)
	target_link_libraries( signLanguage "$ENV{LEAP_SDK}/lib/x64/Leap.lib" )
endif(WIN32)

# Find the QtWidgets library
find_package(Qt5Widgets REQUIRED)

# Use the Widgets module from Qt 5.
target_link_libraries(signLanguage Qt5::Widgets)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../)

