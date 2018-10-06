//
// Created by romain on 04/10/18.
//

#include "../NetworkSession.h"
#include "NetworkClientHandler.h"
#include "HookNetworkServer.h"


NetworkClientHandler::NetworkClientHandler(NetworkController &controller, HookNetworkServer &server)
        : _controller(&controller),
          _server(&server)
{}


void NetworkClientHandler::onConnect(ptr<NetworkSession> session) const {
    printf("[client %zu]: connected\n", session->getId());
    _server->getClients()[session->getId()] = _server->clientProvider(session);
    _controller->onConnect(_server->getClients()[session->getId()].get());
}

void NetworkClientHandler::onReceived(ptr<NetworkSession> session, const char *data, sizet size) const {
    NetworkClient *client = _server->getClients()[session->getId()].get();

    try {
        auto msg = client->read(data, size);
        std::cout << "[client " << session->getId() << "]: recv " << *msg << std::endl;
        _controller->parseMessage(client, msg.get());
    } catch(std::exception &e) {
        printf("[client %zu]: invalid data received, client kicked\n", session->getId());
        client->kick();
    }
}


void NetworkClientHandler::onSent(ptr<NetworkSession> session, const char *data, sizet size) const {
    NetworkClient *client = _server->getClients()[session->getId()].get();

    auto msg = client->read(data, size);
    std::cout << "[client " << session->getId() << "]: sent " << *msg << std::endl;
}


void NetworkClientHandler::onDisconnect(ptr<NetworkSession> session, error_code const &error) const {
    if (error)
        printf("[client %zu]: reason: %s\n", session->getId(), error.message().c_str());
    printf("[client %zu]: disconnected\n", session->getId());
    _controller->onDisconnect(_server->getClients()[session->getId()].get(), error);
    _server->getClients().erase(session->getId());
}
