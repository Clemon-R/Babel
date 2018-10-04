//
// Created by romain on 04/10/18.
//

#ifndef SERVER_SERVERCONTROLLER_H
#define SERVER_SERVERCONTROLLER_H


#include "../shared/hook/NetworkController.h"
#include "BabelConnector.h"
#include "../protocol/HelloConnectMessage.h"

class ServerController : public NetworkController {
public:
    void onConnect(NetworkClient *client) override;
    void onDisconnect(NetworkClient *client, error_code const &error) override;
    void onHello(NetworkClient *client, HelloConnectMessage *msg);

    void setConnector(BabelConnector &connector) {
        _connector = &connector;
    }
protected:
    void defineMessageHandlers(handlers_t &handlers) override;

private:
    BabelConnector *_connector;
};


#endif //SERVER_SERVERCONTROLLER_H
