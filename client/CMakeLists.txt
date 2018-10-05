cmake_minimum_required(VERSION 3.10)
project(babel CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -std=c++17")

if (UNIX) #Debug Qt on Unix
file(WRITE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/qt.conf [Paths]\nPrefix=${CONAN_QT_ROOT})
file(MAKE_DIRECTORY ${CONAN_QT_ROOT}/lib/fonts/)
configure_file(resources/default.ttf ${CONAN_QT_ROOT}/lib/fonts/default.ttf COPYONLY)
endif (UNIX)

include_directories(
	${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}
)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

# Client C++ Sources
set(CLIENT_SOURCES
	src/main.cpp
	src/Exception.cpp
	src/codec/Opus.cpp
	src/sound/Microphone.cpp
	src/sound/Speaker.cpp
	src/forms/mainwindow.cpp
	src/forms/livewindow.cpp
	src/forms/soundmanagerwindow.cpp
	src/forms/receptioncallwindow.cpp
)

# Client C++ headers
set(CLIENT_HEADERS
	src/Exception.hpp
	src/codec/Opus.hpp
	src/sound/Config.hpp
	src/sound/Microphone.hpp
	src/sound/Speaker.hpp
	src/forms/mainwindow.h
	src/forms/livewindow.h
	src/forms/soundmanagerwindow.h
	src/forms/receptioncallwindow.h
)

# Client Qt Interface
set(CLIENT_FORMS
	src/forms/mainwindow.ui
	src/forms/livewindow.ui
	src/forms/soundmanagerwindow.ui
	src/forms/receptioncallwindow.ui
)

# Client Qt Resource
set(CLIENT_RESOURCES
	resources.qrc
)

# Shared libraries
set(CLIENT_LIBRARIES
	Qt5::Widgets
	Qt5::Core
	Qt5::Gui
)

# Client convert .ui
qt5_wrap_ui(UIC_SOURCES ${CLIENT_FORMS})
qt5_add_resources(RCC_SOURCES ${CLIENT_RESOURCES})

# Client compilation
add_executable(babel_client ${CLIENT_RESOURCES} ${CLIENT_SOURCES} ${CLIENT_HEADERS} ${UIC_SOURCES} ${RCC_SOURCES})

target_link_libraries(babel_client ${CONAN_LIBS})
target_link_libraries(babel_client ${CLIENT_LIBRARIES})
