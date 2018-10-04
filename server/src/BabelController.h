//
// Created by romain on 04/10/18.
//

#ifndef SERVER_BABELCONTROLLER_H
#define SERVER_BABELCONTROLLER_H


#include "shared/hook/NetworkController.h"
#include "BabelServer.h"
#include "BabelClient.h"

class BabelController : public NetworkController<BabelClient> {
public:
    void setServer(BabelServer &server) {
        _server = &server;
    }

protected:
    void defineMessageHandlers(handlers_t &handlers) override;
    void onConnect(BabelClient *client) override;
    void onDisconnect(BabelClient *client, error_code &error) override;

private:
    BabelServer *_server;
};


#endif //SERVER_BABELCONTROLLER_H
