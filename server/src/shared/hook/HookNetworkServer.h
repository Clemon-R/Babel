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

using clients_t = std::unordered_map<session_id, std::unique_ptr<NetworkClient>>;

class HookNetworkServer: public NetworkServer {
public:
    explicit HookNetworkServer(NetworkController &controller, boost::uint16_t port = RANDOM_PORT);
    virtual ~HookNetworkServer() {}

    void run() override;
    clients_t &getClients();

    virtual std::unique_ptr<NetworkClient> clientProvider(ptr<NetworkSession> session) = 0;

private:
    NetworkClientHandler _handler;
    NetworkController *_controller;
    clients_t _clients;
};

#endif //SERVER_HOOKNETWORKSERVER_H
