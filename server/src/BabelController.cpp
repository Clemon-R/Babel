//
// Created by romain on 04/10/18.
//

#include "BabelController.h"
#include "protocol/HelloConnectMessage.h"

void BabelController::onConnect(NetworkClient *client) {
    client->send(HelloConnectMessage());
}

void BabelController::onDisconnect(NetworkClient *client, error_code const &error) {

}

void BabelController::onHello(BabelClient *client, HelloConnectMessage *msg) {

}

void BabelController::onCallRequest(BabelClient *client, CallRequestMessage *msg) {

}

void BabelController::onLogin(BabelClient *client, LoginMessage *msg) {

}

void BabelController::onCallRefused(BabelClient *client, CallRefusedMessage *msg) {

}
