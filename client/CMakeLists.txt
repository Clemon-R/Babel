cmake_minimum_required(VERSION 3.10)
project(client CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_AUTOMOC ON)

file(WRITE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/qt.conf [Paths]\nPrefix=${CONAN_QT_ROOT})
#file(WRITE ${CMAKE_SOURCE_DIRECTORY}/qt.conf [Paths]\nPrefix=${CONAN_QT_ROOT})

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
        )
set(HEADERS
        src/Exception.hpp
        src/codec/Opus.hpp
        src/sound/Config.hpp
        src/sound/Microphone.hpp
        src/sound/Speaker.hpp
)

# User interface files
set(FORMS
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

add_executable(client ${UIS} ${RESOURCES} ${SOURCES} ${HEADERS} ${UIC_SOURCES} ${RCC_SOURCES})

target_link_libraries(client ${CONAN_LIBS})
target_link_libraries(client ${LIBRARIES})
