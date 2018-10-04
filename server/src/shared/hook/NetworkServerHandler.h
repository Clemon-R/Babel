//
// Created by romain on 04/10/18.
//

#ifndef SERVER_ABWORKHANDLER_H
#define SERVER_ABWORKHANDLER_H


#include "../NetworkSessionHandler.h"
#include "NetworkController.h"

class HookNetworkConnector;

class NetworkServerHandler: public NetworkSessionHandler {
public:
    NetworkServerHandler(NetworkController &controller, HookNetworkConnector &connector);

    void onConnect(ptr<NetworkSession> session) const override;
    void onReceived(ptr<NetworkSession> session, const char *data, sizet size) const override;
    void onSent(ptr<NetworkSession> session, const char *data, sizet size) const override;
    void onDisconnect(ptr<NetworkSession> session, error_code const &error) const override;

private:
    NetworkController *_controller;
    HookNetworkConnector *_connector;
};


#endif //SERVER_ABWORKHANDLER_H
