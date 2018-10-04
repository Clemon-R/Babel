//
// Created by romain on 04/10/18.
//

#include "BabelServer.h"
#include "BabelClient.h"

BabelServer::BabelServer(NetworkController<BabelClient> &controller, boost::uint16_t port)
        : HookNetworkServer<BabelClient>(controller, port)
{}

std::unique_ptr<BabelClient> BabelServer::clientProvider(ptr<NetworkSession> session) {
    return std::make_unique<BabelClient>(session);
}
