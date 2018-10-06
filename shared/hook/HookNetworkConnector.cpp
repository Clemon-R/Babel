//
// Created by romain on 04/10/18.
//

#include "HookNetworkConnector.h"

HookNetworkConnector::HookNetworkConnector(NetworkController &controller)
        : NetworkConnector(&_handler),
          _client(),
          _handler(controller, *this),
          _controller(&controller)
{}

NetworkClient *HookNetworkConnector::getClient() {
    return _client.get();
}

void HookNetworkConnector::setClient(std::unique_ptr<NetworkClient> instance) {
    _client = std::move(instance);
}

std::unique_ptr<NetworkClient> HookNetworkConnector::clientProvider(ptr<NetworkSession> session) {
    return std::unique_ptr<NetworkClient>(new NetworkClient(session));
}

void HookNetworkConnector::connect(std::string const &host, std::string const &port, bool useThread) {
    _controller->init();
    NetworkConnector::connect(host, port, useThread);
}

void HookNetworkConnector::connect(std::string const &host, boost::uint16_t port, bool useThread) {
    _controller->init();
    NetworkConnector::connect(host, port, useThread);
}
