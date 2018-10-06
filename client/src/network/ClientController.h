//
// Created by raphael on 06/10/18.
//

#ifndef BABEL_CLIENTCONTROLLER_H
#define BABEL_CLIENTCONTROLLER_H


#include <shared/hook/NetworkController.h>
#include <protocol/HelloConnectMessage.h>

class ClientController : public NetworkController {
public:
    void onConnect(NetworkClient *client) override;
    void onDisconnect(NetworkClient *client, error_code const &error) override;

protected:

    void defineMessageHandlers(handlers_t &handlers) override {
        handlers[HelloConnectMessage::OPCODE] = handler(this, &ClientController::onHello);
    }

private:
    void onHello(NetworkClient *user, HelloConnectMessage *msg);
};


#endif //BABEL_CLIENTCONTROLLER_H
