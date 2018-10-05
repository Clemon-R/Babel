//
// Created by romain on 04/10/18.
//

#include "BabelServer.h"
#include "BabelClient.h"

BabelServer::BabelServer(NetworkController &controller, boost::uint16_t port)
        : HookNetworkServer(controller, port)
{}

std::unique_ptr<NetworkClient> BabelServer::clientProvider(ptr<NetworkSession> session) {
    return std::make_unique<BabelClient>(session);
}

BabelClient *BabelServer::find(std::string const &name) {
    BabelClient *client = nullptr;

    //TODO: find client by name

    return client;
}
