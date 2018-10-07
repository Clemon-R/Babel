//
// Created by romain on 04/10/18.
//

#include "BabelServer.h"
#include "BabelUser.h"

BabelServer::BabelServer(NetworkController &controller, boost::uint16_t port)
        : HookNetworkServer(controller, port)
{}

std::unique_ptr<NetworkClient> BabelServer::clientProvider(ptr<NetworkSession> session) {
    return std::make_unique<BabelUser>(session);
}

BabelUser *BabelServer::find(std::string const &name) {
    for (auto &client: getClients()) {
        auto *user = dynamic_cast<BabelUser *>(client.second.get());

        if (user->pseudo() == name)
            return user;
    }
    return nullptr;
}

void BabelServer::sendToAll(NetworkClient *sender, NetworkMessage &&msg) {
    for (auto &client: getClients())
        if (client.first != sender->getId())
            client.second->send(msg);
}
