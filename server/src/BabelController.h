//
// Created by romain on 04/10/18.
//

#ifndef SERVER_BABELCONTROLLER_H
#define SERVER_BABELCONTROLLER_H


#include "shared/hook/NetworkController.h"
#include "BabelServer.h"
#include "BabelClient.h"
#include "protocol/HelloConnectMessage.h"

class BabelController : public NetworkController {
public:
    void onConnect(NetworkClient *client) override;
    void onDisconnect(NetworkClient *client, error_code const &error) override;

    void onHello(BabelClient *client, HelloConnectMessage *msg);

    void setServer(BabelServer &server) {
        _server = &server;
    }
protected:
    void defineMessageHandlers(handlers_t &handlers) override;

private:
    BabelServer *_server;
};


#endif //SERVER_BABELCONTROLLER_H
