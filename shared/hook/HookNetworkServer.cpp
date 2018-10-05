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

void HookNetworkServer::run() {
    _controller->init();
    NetworkServer::run();
}

clients_t &HookNetworkServer::getClients() {
    return _clients;
}