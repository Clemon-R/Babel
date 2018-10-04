//
// Created by romain on 04/10/18.
//

#include "../NetworkSession.h"
#include "NetworkServerHandler.h"
#include "HookNetworkConnector.h"

NetworkServerHandler::NetworkServerHandler(NetworkController &controller, HookNetworkConnector &connector)
        : _controller(&controller),
          _connector(&connector)
{}


void NetworkServerHandler::onConnect(ptr<NetworkSession> session) const {
    printf("[server]: connected\n");
    _connector->setClient(_connector->clientProvider(session));
    _controller->onConnect(_connector->getClient());
}


void NetworkServerHandler::onReceived(ptr<NetworkSession> session, const char *data, sizet size) const {
    try {
        auto msg = _connector->getClient()->read(data, size);
        std::cout << "[server]: recv " << *msg << std::endl;
        _controller->parseMessage(_connector->getClient(), msg.get());
    } catch(std::exception &e) {
        onDisconnect(session, error_code());
        return;
    }
}


void NetworkServerHandler::onSent(ptr<NetworkSession> session, const char *data, sizet size) const {
    auto msg = _connector->getClient()->read(data, size);
    std::cout << "[server] sent " << *msg << std::endl;
}


void NetworkServerHandler::onDisconnect(ptr<NetworkSession> session, error_code const &error) const {
    if (error)
        printf("[server]: error: %s\n", error.message().c_str());
    printf("[server]: disconnected\n");
    _controller->onDisconnect(_connector->getClient(), error);
}
