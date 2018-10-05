#cmake >= 3.10 required for compile c++17 code
cmake_minimum_required(VERSION 3.10)
project(server CXX)

#c++17: needed for inline variables
add_definitions("-std=c++17")
add_definitions(-DBOOST_ALL_NO_LIB -DBOOST_ALL_DYN_LINK -DBOOST_LOG_DYN_LINK)
include(conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall")

add_executable(babel_server src/main.cpp src/shared/hook/NetworkServerHandler.h src/shared/hook/NetworkServerHandler.cpp src/shared/NetworkServer.cpp src/shared/NetworkServer.h src/shared/NetworkSession.cpp src/shared/NetworkSession.h src/shared/Network.h src/shared/NetworkSessionHandler.h src/shared/BinaryReader.cpp src/shared/BinaryReader.h src/shared/BinaryWriter.cpp src/shared/BinaryWriter.h src/shared/NetworkConnector.cpp src/shared/NetworkConnector.h src/protocol/HelloConnectMessage.h src/shared/hook/NetworkMessage.h src/shared/hook/NetworkController.h src/shared/hook/NetworkClient.cpp src/shared/hook/NetworkClient.h src/shared/hook/NetworkProtocol.h src/BabelServer.cpp src/BabelServer.h src/shared/hook/NetworkClientHandler.cpp src/shared/hook/NetworkClientHandler.h src/shared/hook/HookNetworkServer.h src/shared/hook/HookNetworkServer.cpp src/BabelController.cpp src/BabelController.h src/BabelClient.cpp src/BabelClient.h src/shared/hook/HookNetworkConnector.cpp src/shared/hook/HookNetworkConnector.h src/client/ServerController.cpp src/client/ServerController.h src/client/BabelConnector.cpp src/client/BabelConnector.h src/protocol/LoginMessage.h src/protocol/LoginSuccessMessage.h src/protocol/LoginFailedMessage.h src/protocol/UpdateContactMessage.h src/shared/Util.h)

target_link_libraries(babel_server CONAN_PKG::boost_asio)