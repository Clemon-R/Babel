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

    void startHost();
    boost::uint16_t getPort();
    void connect(std::string const &host, uint16_t port);
    void addContact(std::string const &contact);
    void delContact(std::string const &contact);
    void send(NetworkMessage const &message);

private:
    ClientController _controller;
    HookNetworkConnector _connector;
    HookNetworkServer _server;
    std::mutex _locker;

    std::vector<std::string> _contacts;
};


#endif //BABEL_CLIENTMANAGER_H
