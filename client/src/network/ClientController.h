//
// Created by romain on 06/10/18.
//

#ifndef BABEL_CLIENTCONTROLLER_H
#define BABEL_CLIENTCONTROLLER_H


#include <shared/hook/NetworkController.h>
#include <protocol/HelloConnectMessage.h>
#include <protocol/AddContactMessage.h>
#include <protocol/DelContactMessage.h>
#include <protocol/LoginFailedMessage.h>
#include <protocol/LoginSuccessMessage.h>
#include <protocol/ErrorResponseMessage.h>
#include <protocol/CallRequestMessage.h>
#include <protocol/VoiceDataMessage.h>
#include <protocol/CallRefusedMessage.h>
#include <protocol/ConnectionEtablishedMessage.h>
class ClientManager;

class ClientController : public NetworkController {
public:
    ClientController(ClientManager *manager) : _manager(manager){};

    void onConnect(NetworkClient *client) override;
    void onDisconnect(NetworkClient *client, error_code const &error) override;

protected:

    void defineMessageHandlers(handlers_t &handlers) override {
        handlers[HelloConnectMessage::OPCODE] = handler(this, &ClientController::onServerReady);
        handlers[AddContactMessage::OPCODE] = handler(this, &ClientController::onNewContact);
        handlers[DelContactMessage::OPCODE] = handler(this, &ClientController::onDisconnectedContact);
        handlers[LoginFailedMessage::OPCODE] = handler(this, &ClientController::onLoginFailed);
        handlers[LoginSuccessMessage::OPCODE] = handler(this, &ClientController::onLoginSuccess);
        handlers[ErrorResponseMessage::OPCODE] = handler(this, &ClientController::onServerError);
        handlers[CallRequestMessage::OPCODE] = handler(this, &ClientController::onCallRequest);
        handlers[CallRefusedMessage::OPCODE] = handler(this, &ClientController::onCallRefused);
        handlers[VoiceDataMessage::OPCODE] = handler(this, &ClientController::onVoiceDataReceived);
        handlers[ConnectionEtablishedMessage::OPCODE] = handler(this, &ClientController::onContactReady);
    }

private:
    void onServerReady(NetworkClient *user, HelloConnectMessage *msg);
    void onNewContact(NetworkClient *user, AddContactMessage *msg);
    void onDisconnectedContact(NetworkClient *user, DelContactMessage *msg);
    void onLoginFailed(NetworkClient *user, LoginFailedMessage *msg);
    void onLoginSuccess(NetworkClient *user, LoginSuccessMessage *msg);
    void onServerError(NetworkClient *user, ErrorResponseMessage *msg);
    void onCallRequest(NetworkClient *user, CallRequestMessage *msg);
    void onCallRefused(NetworkClient *user, CallRefusedMessage *msg);
    void onContactReady(NetworkClient *user, ConnectionEtablishedMessage *msg);
    void onVoiceDataReceived(NetworkClient *user, VoiceDataMessage *msg);

private:
    ClientManager *_manager;
};


#endif //BABEL_CLIENTCONTROLLER_H
