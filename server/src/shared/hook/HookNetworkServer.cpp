//
// Created by romain on 04/10/18.
//

#include "HookNetworkServer.h"

template<class T>
HookNetworkServer<T>::HookNetworkServer(NetworkController<T> &controller, uint16_t port)
        : NetworkServer(&_handler, port),
          _handler(controller, *this),
          _controller(&controller),
          _clients()
{}

template<class T>
void HookNetworkServer<T>::run() {
    _controller->init();
    NetworkServer::run();
}

template<class T>
clients_t<T> &HookNetworkServer<T>::getClients() {
    return _clients;
}
