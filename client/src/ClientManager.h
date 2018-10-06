//
// Created by romain on 06/10/18.
//

#ifndef BABEL_CLIENTMANAGER_H
#define BABEL_CLIENTMANAGER_H


#include <shared/hook/HookNetworkConnector.h>
#include <client/src/network/ClientController.h>
#include <shared/hook/HookNetworkServer.h>

class ClientManager {
public:
    ClientManager();

    void

private:
    ClientController _controller;
    HookNetworkConnector _connector;
    HookNetworkServer _server;
    std::mutex _locker;
};


#endif //BABEL_CLIENTMANAGER_H
