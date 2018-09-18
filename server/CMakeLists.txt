cmake_minimum_required(VERSION 3.10)
project(server CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Wall")
add_definitions("-std=c++17")

add_executable(server src/main.cpp)

target_link_libraries(server ${CONAN_LIBS})