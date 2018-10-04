//
// Created by romain on 04/10/18.
//

#ifndef SERVER_BABELSERVER_H
#define SERVER_BABELSERVER_H


#include "shared/Network.h"
#include "shared/NetworkServer.h"
#include "shared/hook/NetworkClient.h"
#include "shared/hook/HookNetworkServer.h"
#include "BabelClient.h"

class BabelServer: public HookNetworkServer<BabelClient> {
public:
    explicit BabelServer(NetworkController<BabelClient> &controller, boost::uint16_t port = RANDOM_PORT);

protected:
    std::unique_ptr<BabelClient> clientProvider(ptr<NetworkSession> session) override;
};


#endif //SERVER_BABELSERVER_H
