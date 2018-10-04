//
// Created by romain on 04/10/18.
//

#ifndef SERVER_HOOKNETWORKCONNECTOR_H
#define SERVER_HOOKNETWORKCONNECTOR_H


#include "../NetworkConnector.h"
#include "NetworkController.h"
#include "NetworkServerHandler.h"

class HookNetworkConnector : public NetworkConnector {
public:
    HookNetworkConnector(std::string const &host, boost::uint16_t port, NetworkController &controller);
    HookNetworkConnector(std::string const &host, std::string const &port, NetworkController &controller);

    NetworkClient *getClient();
    void setClient(std::unique_ptr<NetworkClient> instance);

    void connect(bool useThread = false) override;
    virtual std::unique_ptr<NetworkClient> clientProvider(ptr<NetworkSession> session);

private:
    std::unique_ptr<NetworkClient> _client;
    NetworkServerHandler _handler;
    NetworkController *_controller;
};


#endif //SERVER_HOOKNETWORKCONNECTOR_H
