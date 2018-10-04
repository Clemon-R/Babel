//
// Created by romain on 04/10/18.
//

#ifndef SERVER_HOOKNETWORKHANDLER_H
#define SERVER_HOOKNETWORKHANDLER_H


#include "../NetworkSessionHandler.h"
#include "NetworkController.h"

template<class T>
class HookNetworkServer;

template<class T>
class NetworkClientHandler: public NetworkSessionHandler {
public:
    NetworkClientHandler(NetworkController<T> &controller, HookNetworkServer<T> &server);

    void onConnect(ptr<NetworkSession> session) const override;
    void onReceived(ptr<NetworkSession> session, const char *data, sizet size) const override;
    void onSent(ptr<NetworkSession> session, const char *data, sizet size) const override;
    void onDisconnect(ptr<NetworkSession> session, error_code const &error) const override;

private:
    NetworkController<T> *_controller;
    HookNetworkServer<T> *_server;
};


#endif //SERVER_HOOKNETWORKHANDLER_H
