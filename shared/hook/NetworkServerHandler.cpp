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
    printf("[network]: connected\n");
    _connector->setClient(_connector->clientProvider(session));
    _controller->onConnect(_connector->getClient());
}


void NetworkServerHandler::onReceived(ptr<NetworkSession> session, const char *data, sizet size) const {
    try {
        auto msg = _connector->getClient()->read(data, size);
        std::cout << "[network]: recv " << *msg << std::endl;
        _controller->parseMessage(_connector->getClient(), msg.get());
    } catch(std::exception &e) {
        session->getSocket().close();
    }
}


void NetworkServerHandler::onSent(ptr<NetworkSession> session, const char *data, sizet size) const {
    try {
        std::unique_ptr<NetworkMessage> tmp(std::move(_connector->getClient()->read(data, size)));
        NetworkMessage  *msg = tmp.release();

        std::cout << "[network]: sent " << *msg << std::endl;
    } catch(std::exception &e) {
        std::cout << "[network]: sent invalid data, server will kick you" << std::endl;
    }
}


void NetworkServerHandler::onDisconnect(ptr<NetworkSession> session, error_code const &error) const {
    if (error)
        printf("[network]: socket closed, reason: %s\n", error.message().c_str());
    printf("[network]: disconnected\n");
    _controller->onDisconnect(_connector->getClient(), error);
}
