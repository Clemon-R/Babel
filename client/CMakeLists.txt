cmake_minimum_required(VERSION 3.10)
project(babel_client CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_AUTOMOC ON)

if (UNIX)
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

# Source files
set(SOURCES
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
set(HEADERS
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

# User interface files
set(FORMS
        src/forms/mainwindow.ui
        src/forms/livewindow.ui
        src/forms/soundmanagerwindow.ui
        src/forms/receptioncallwindow.ui
        )

# Resource files
set(RESOURCES
        resources.qrc
        )

# Shared libraries
set(LIBRARIES
        Qt5::Widgets
        Qt5::Core
        Qt5::Gui
        )
qt5_wrap_ui(UIC_SOURCES ${FORMS})
qt5_add_resources(RCC_SOURCES ${RESOURCES})
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -std=c++17")

add_executable(babel_client ${UIS} ${RESOURCES} ${SOURCES} ${HEADERS} ${UIC_SOURCES} ${RCC_SOURCES})

target_link_libraries(babel_client ${CONAN_LIBS})
target_link_libraries(babel_client ${LIBRARIES})
