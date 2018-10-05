#cmake >= 3.10 required for compile c++17 code
cmake_minimum_required(VERSION 3.10)
project(server CXX)

#c++17: needed for inline variables
add_definitions("-std=c++17")
add_definitions(-DBOOST_ALL_NO_LIB -DBOOST_ALL_DYN_LINK -DBOOST_LOG_DYN_LINK)
include(conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall")

add_executable(babel_server src/main.cpp ../shared/hook/NetworkServerHandler.h ../shared/hook/NetworkServerHandler.cpp ../shared/NetworkServer.cpp ../shared/NetworkServer.h ../shared/NetworkSession.cpp ../shared/NetworkSession.h ../shared/Network.h ../shared/NetworkSessionHandler.h ../shared/BinaryReader.cpp ../shared/BinaryReader.h ../shared/BinaryWriter.cpp ../shared/BinaryWriter.h ../shared/NetworkConnector.cpp ../shared/NetworkConnector.h ../protocol/HelloConnectMessage.h ../shared/hook/NetworkMessage.h ../shared/hook/NetworkController.h ../shared/hook/NetworkClient.cpp ../shared/hook/NetworkClient.h ../shared/hook/NetworkProtocol.h src/BabelServer.cpp src/BabelServer.h ../shared/hook/NetworkClientHandler.cpp ../shared/hook/NetworkClientHandler.h ../shared/hook/HookNetworkServer.h ../shared/hook/HookNetworkServer.cpp src/BabelController.cpp src/BabelController.h src/BabelUser.cpp src/BabelUser.h ../shared/hook/HookNetworkConnector.cpp ../shared/hook/HookNetworkConnector.h src/client/ServerController.cpp src/client/ServerController.h src/client/BabelConnector.cpp src/client/BabelConnector.h ../protocol/LoginMessage.h ../protocol/LoginSuccessMessage.h ../protocol/LoginFailedMessage.h ../protocol/AddContactMessage.h ../shared/Util.h ../protocol/CallRequestMessage.h ../protocol/ErrorResponseMessage.h ../protocol/CallRefusedMessage.h ../protocol/VoiceDataMessage.h)

target_link_libraries(babel_server CONAN_PKG::boost_asio)