//
// Created by romain on 04/10/18.
//

#ifndef SERVER_BABELSERVER_H
#define SERVER_BABELSERVER_H


#include "../../shared/Network.h"
#include "../../shared/NetworkServer.h"
#include "../../shared/hook/NetworkClient.h"
#include "../../shared/hook/HookNetworkServer.h"
#include "BabelUser.h"

class BabelServer: public HookNetworkServer {
public:
    BabelServer(NetworkController &controller, boost::uint16_t port = RANDOM_PORT);

    std::unique_ptr<NetworkClient> clientProvider(ptr<NetworkSession> session) override;

    void sendToAll(NetworkClient *sender, NetworkMessage &&msg);
    BabelUser *find(std::string const &pseudo);
};


#endif //SERVER_BABELSERVER_H
