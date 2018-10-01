cmake_minimum_required(VERSION 3.10)
project(server CXX)

add_definitions("-std=c++11")
add_definitions(-DBOOST_ALL_NO_LIB -DBOOST_ALL_DYN_LINK -DBOOST_LOG_DYN_LINK)
include(conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall")

add_executable(babel_server src/main.cpp src/shared/NetworkServer.cpp src/shared/NetworkServer.h src/shared/NetworkSession.cpp src/shared/NetworkSession.h src/shared/Network.h src/shared/NetworkSessionHandler.h src/Handler.cpp src/Handler.h src/shared/BinaryReader.cpp src/shared/BinaryReader.h src/shared/BinaryWriter.cpp src/shared/BinaryWriter.h src/shared/NetworkConnector.cpp src/shared/NetworkConnector.h)

target_link_libraries(babel_server CONAN_PKG::boost_serialization)
target_link_libraries(babel_server CONAN_PKG::boost_asio)
target_link_libraries(babel_server CONAN_PKG::boost_interprocess)