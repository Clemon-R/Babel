//
// Created by romain on 06/10/18.
//

#ifndef BABEL_CLIENTMANAGER_H
#define BABEL_CLIENTMANAGER_H


#include <shared/hook/HookNetworkConnector.h>
#include <shared/hook/HookNetworkServer.h>
class LiveWindow;
class ClientController;

class ClientManager {
public:
    ClientManager(LiveWindow *, const std::string &);

    void startHost();
    boost::uint16_t getPort();
    void connect(std::string const &host, uint16_t port);
    void addContact(std::string const &contact);
    void delContact(std::string const &contact);
    void send(NetworkMessage const &message);

    std::vector<std::string> const &getContacts() const;

    void    connectSuccess();
    void    authentication();
    void    authenticationSuccess();
    void    authenticationFailed();
private:
    std::unique_ptr<ClientController> _controller;
    HookNetworkConnector _connector;
    HookNetworkServer _server;
    std::mutex _locker;
    LiveWindow *_ui;

    std::string _username;
    std::vector<std::string> _contacts;
};


#endif //BABEL_CLIENTMANAGER_H
