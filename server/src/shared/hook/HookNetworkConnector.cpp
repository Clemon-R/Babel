//
// Created by romain on 04/10/18.
//

#include "HookNetworkConnector.h"

HookNetworkConnector::HookNetworkConnector(std::string const &host, boost::uint16_t port, NetworkController &controller)
        : NetworkConnector(host, port, &_handler),
          _handler(controller, *this),
          _controller(&controller)
{}

HookNetworkConnector::HookNetworkConnector(std::string const &host, std::string const &port, NetworkController &controller)
        : NetworkConnector(host, port, &_handler),
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
    return std::make_unique<NetworkClient>(session);
}

void HookNetworkConnector::connect(bool useThread) {
    _controller->init();
    NetworkConnector::connect(useThread);
}
