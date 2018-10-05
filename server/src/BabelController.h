//
// Created by romain on 04/10/18.
//

#ifndef SERVER_BABELCONTROLLER_H
#define SERVER_BABELCONTROLLER_H


#include "../../shared/hook/NetworkController.h"
#include "BabelServer.h"
#include "BabelUser.h"
#include "../../protocol/HelloConnectMessage.h"
#include "../../protocol/CallRequestMessage.h"
#include "../../protocol/LoginMessage.h"
#include "../../protocol/CallRefusedMessage.h"

class BabelController : public NetworkController {
public:
    void onConnect(NetworkClient *client) override;
    void onDisconnect(NetworkClient *client, error_code const &error) override;

    void onCallRequest(BabelUser *client, CallRequestMessage *msg);
    void onLogin(BabelUser *client, LoginMessage *msg);
    void onCallRefused(BabelUser *client, CallRefusedMessage *msg);

    void setServer(BabelServer &server) {
        _server = &server;
    }

protected:

    void defineMessageHandlers(handlers_t &handlers) override {
        handlers[CallRequestMessage::OPCODE] = handler(this, &BabelController::onCallRequest);
        handlers[HelloConnectMessage::OPCODE] = handler(this, &BabelController::onLogin);
        handlers[HelloConnectMessage::OPCODE] = handler(this, &BabelController::onCallRefused);
    }

private:
    BabelServer *_server;
};


#endif //SERVER_BABELCONTROLLER_H
