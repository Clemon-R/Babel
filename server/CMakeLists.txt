cmake_minimum_required(VERSION 3.10)
project(server CXX)

include(conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Wall")
add_definitions("-std=c++11")

add_executable(babel_server src/main.cpp src/NetworkServer.cpp src/NetworkServer.h src/NetworkSession.cpp src/NetworkSession.h src/Network.h src/NetworkSessionHandler.h)

target_link_libraries(babel_server ${CONAN_LIBS})