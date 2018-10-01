//
// Created by romain on 22/09/18.
//

#include "Handler.h"
#include "shared/NetworkSession.h"

void Handler::onConnect(ptr<NetworkSession> session) const {
    if (_serv)
        printf("x");
    printf("connected %zu\n", session->getId());
    if (_serv)
        session->send("lol", 3);
}

void Handler::onReceived(ptr<NetworkSession> session, const char *data, sizet size) const {
    if (_serv)
        printf("x");
    printf("received : [");
    for (sizet i=0; i < size; ++i)
        printf("%d.", data[i]);
    printf("]\n");
}

void Handler::onSent(ptr<NetworkSession> session, const char *data, sizet size) const {
    if (_serv)
        printf("x");
    printf("sent : [");
    for (sizet i=0; i < size; ++i)
        printf("%d.", data[i]);
    printf("]\n");
}

void Handler::onDisconnect(ptr<NetworkSession> session, error_code const &error) const {
    if (_serv)
        printf("x");
    if (error)
        printf("client %zu error: %s\n", session->getId(), error.message().c_str());
    printf("disconnected %zu\n", session->getId());
}
