//
// Created by raphael on 06/10/18.
//

#include <protocol/LoginMessage.h>
#include "ClientController.h"

void ClientController::onHello(NetworkClient *user, HelloConnectMessage *msg) {
    user->send(LoginMessage("myusername"));
}

void ClientController::onConnect(NetworkClient *client) {

}

void ClientController::onDisconnect(NetworkClient *client, error_code const &error) {

}
