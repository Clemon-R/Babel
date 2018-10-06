cmake_minimum_required(VERSION 3.10)
project(babel CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)
INCLUDE_DIRECTORIES(${CONAN_INCLUDE_DIRS})

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -std=c++17 -g3")
#add_definitions(-DBOOST_ALL_NO_LIB -DBOOST_ALL_DYN_LINK -DBOOST_LOG_DYN_LINK)

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
#find_package(Boost 1.68.0 REQUIRED system thread regex)
#IF(Boost_FOUND)
#  INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
#  LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
#ENDIF(Boost_FOUND)*/

# Client C++ Sources
set(CLIENT_SOURCES
	client/src/main.cpp client/src/Exception.cpp
	client/src/codec/Opus.cpp
	client/src/sound/Microphone.cpp
	client/src/sound/Speaker.cpp
	client/src/forms/mainwindow.cpp
	client/src/forms/livewindow.cpp
	client/src/forms/soundmanagerwindow.cpp
    client/src/forms/receptioncallwindow.cpp
        client/src/network/ClientController.cpp
        )

# Client C++ headers
set(CLIENT_HEADERS
        client/src/Exception.hpp
	client/src/codec/Opus.hpp
	client/src/sound/Config.hpp
	client/src/sound/Microphone.hpp
	client/src/sound/Speaker.hpp
	client/src/forms/mainwindow.h
	client/src/forms/livewindow.h
	client/src/forms/soundmanagerwindow.h
	client/src/forms/receptioncallwindow.h
        client/src/network/ClientController.h)

# Client Qt Interface
set(CLIENT_FORMS
	client/src/forms/mainwindow.ui
	client/src/forms/livewindow.ui
	client/src/forms/soundmanagerwindow.ui
	client/src/forms/receptioncallwindow.ui
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

set(SHARED_FILES
	shared/hook/NetworkServerHandler.h
	shared/hook/NetworkServerHandler.cpp
	shared/NetworkServer.cpp
	shared/NetworkServer.h
	shared/NetworkSession.cpp
	shared/NetworkSession.h
	shared/Network.h
	shared/NetworkSessionHandler.h
	shared/BinaryReader.cpp
	shared/BinaryReader.h
	shared/BinaryWriter.cpp
	shared/BinaryWriter.h
	shared/NetworkConnector.cpp
	shared/NetworkConnector.h
	shared/hook/NetworkClientHandler.cpp
	shared/hook/NetworkClientHandler.h
	shared/hook/HookNetworkServer.h
	shared/hook/HookNetworkServer.cpp
	shared/hook/NetworkMessage.h
	shared/hook/NetworkController.h
	shared/hook/NetworkClient.cpp
	shared/hook/NetworkClient.h
	shared/hook/NetworkProtocol.h
	shared/hook/HookNetworkConnector.cpp
	shared/hook/HookNetworkConnector.h
	shared/Util.h
	protocol/LoginMessage.h
	protocol/LoginSuccessMessage.h
	protocol/LoginFailedMessage.h
	protocol/DelContactMessage.h
	protocol/AddContactMessage.h
	protocol/CallRequestMessage.h
	protocol/ErrorResponseMessage.h
	protocol/CallRefusedMessage.h
	protocol/VoiceDataMessage.h
	protocol/HelloConnectMessage.h
		protocol/ConnectionEtablishedMessage.h)

# Client convert .ui
qt5_wrap_ui(UIC_SOURCES ${CLIENT_FORMS})
qt5_add_resources(RCC_SOURCES ${CLIENT_RESOURCES})

# Client compilation
add_executable(babel_client ${CLIENT_RESOURCES} ${CLIENT_SOURCES} ${SHARED_FILES} ${CLIENT_HEADERS} ${UIC_SOURCES} ${RCC_SOURCES})

target_link_libraries(babel_client CONAN_PKG::portaudio CONAN_PKG::opus CONAN_PKG::Qt CONAN_PKG::boost_asio)
target_link_libraries(babel_client ${CLIENT_LIBRARIES})

SET(USED_LIBS ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY})

add_executable(babel_server 
	server/src/main.cpp
	server/src/BabelServer.cpp
	server/src/BabelServer.h
	server/src/BabelController.cpp
	server/src/BabelController.h
	server/src/BabelUser.cpp
	server/src/BabelUser.h
		${SHARED_FILES}
		)
target_link_libraries(babel_server CONAN_PKG::boost_asio)
