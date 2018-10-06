//
// Created by romain on 04/10/18.
//

#include "HookNetworkServer.h"

HookNetworkServer::HookNetworkServer(NetworkController &controller, uint16_t port)
        : NetworkServer(&_handler, port),
          _handler(controller, *this),
          _controller(&controller),
          _clients()
{}

void HookNetworkServer::run(bool useThread) {
    _controller->init();
    NetworkServer::run(useThread);
}

clients_t &HookNetworkServer::getClients() {
    return _clients;
}

std::unique_ptr<NetworkClient> HookNetworkServer::clientProvider(ptr<NetworkSession> session) {
    return std::unique_ptr<NetworkClient>(new NetworkClient(session));
}
