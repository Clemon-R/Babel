//
// Created by romain on 04/10/18.
//

#ifndef SERVER_HOOKNETWORKSERVER_H
#define SERVER_HOOKNETWORKSERVER_H

#include <unordered_map>
#include "../Network.h"
#include "NetworkClient.h"
#include "NetworkController.h"
#include "../NetworkServer.h"
#include "NetworkClientHandler.h"

template<class T>
using clients_t = std::unordered_map<session_id, std::unique_ptr<T>>;

template<class T>
class HookNetworkServer: public NetworkServer {
public:
    explicit HookNetworkServer(NetworkController<T> &controller, boost::uint16_t port = RANDOM_PORT);
    virtual ~HookNetworkServer() {}

    void run() override;
    clients_t<T> &getClients();

protected:
    virtual std::unique_ptr<T> clientProvider(ptr<NetworkSession> session) = 0;

private:
    NetworkClientHandler<T> _handler;
    NetworkController<T> *_controller;
    clients_t<T> _clients;
};

#endif //SERVER_HOOKNETWORKSERVER_H
