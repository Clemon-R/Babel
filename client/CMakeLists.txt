cmake_minimum_required(VERSION 3.10)
project(client CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Wall")
add_definitions("-std=c++17")

add_executable(client src/main.cpp src/sound/Microphone.hpp src/sound/Microphone.cpp src/Exception.cpp src/Exception.hpp src/sound/Speaker.cpp src/sound/Speaker.hpp src/sound/Config.hpp src/codec/Opus.cpp src/codec/Opus.hpp)

target_link_libraries(client ${CONAN_LIBS})