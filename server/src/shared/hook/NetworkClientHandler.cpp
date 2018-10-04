//
// Created by romain on 04/10/18.
//

#include "../NetworkSession.h"
#include "NetworkClientHandler.h"
#include "HookNetworkServer.h"

template<class T>
NetworkClientHandler<T>::NetworkClientHandler(NetworkController<T> &controller, HookNetworkServer<T> &server)
        : _controller(&controller),
          _server(&server)
{}

template<class T>
void NetworkClientHandler<T>::onConnect(ptr<NetworkSession> session) const {
    printf("[client %zu] connected\n", session->getId());
    _server->getClients()[session->getId()] = std::make_unique<NetworkClient>(session);
}

template<class T>
void NetworkClientHandler<T>::onReceived(ptr<NetworkSession> session, const char *data, sizet size) const {
    printf("received : [");
    for (sizet i=0; i < size; ++i)
        printf("%d.", data[i]);
    printf("]\n");
}

template<class T>
void NetworkClientHandler<T>::onSent(ptr<NetworkSession> session, const char *data, sizet size) const {
    printf("sent : [");
    for (sizet i=0; i < size; ++i)
        printf("%d.", data[i]);
    printf("]\n");
}

template<class T>
void NetworkClientHandler<T>::onDisconnect(ptr<NetworkSession> session, error_code const &error) const {
    if (error)
        printf("client %zu error: %s\n", session->getId(), error.message().c_str());
    printf("disconnected %zu\n", session->getId());
}
