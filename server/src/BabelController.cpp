//
// Created by romain on 04/10/18.
//

#include "BabelController.h"
#include "protocol/HelloConnectMessage.h"

void BabelController::defineMessageHandlers(handlers_t &handlers) {
    handlers[HelloConnectMessage::OPCODE] = handler(this, &BabelController::onHello);
}

void BabelController::onConnect(NetworkClient *client) {
    client->send(HelloConnectMessage());
}

void BabelController::onDisconnect(NetworkClient *client, error_code const &error) {

}

void BabelController::onHello(BabelClient *client, HelloConnectMessage *msg) {

}
