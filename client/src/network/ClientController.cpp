//
// Created by romain on 06/10/18.
//

#include <protocol/LoginMessage.h>
#include <client/src/network/ClientController.h>
#include <client/src/ClientManager.h>
#include "ClientController.h"


void ClientController::onServerReady(NetworkClient *user, HelloConnectMessage *msg) {
    _manager->connectSuccess();
    _manager->authentication();
}

void ClientController::onDisconnect(NetworkClient *client, error_code const &error) {
    if ((!_manager->getImHost() && _manager->getIsCalling()) || (_manager->isHostClient(client->getId()) && _manager->getHostClients() == 1)) {
        _manager->endOfCall();
    }
	if (_manager->isServer(client->getId())) {
		_manager->serverDisconnect();
	}
}

void ClientController::onContactReady(NetworkClient *user, ConnectionEtablishedMessage *msg) {
    _manager->callEtablish();
}

void ClientController::onNewContact(NetworkClient *user, AddContactMessage *msg) {
    for (const std::string &pseudo : msg->newClients){
        _manager->addContact(pseudo);
    }
}

void ClientController::onDisconnectedContact(NetworkClient *user, DelContactMessage *msg) {
    for (const std::string &pseudo : msg->delClients){
        _manager->delContact(pseudo);
    }
}

void ClientController::onLoginFailed(NetworkClient *user, LoginFailedMessage *msg) {
    _manager->authenticationFailed();
}

void ClientController::onLoginSuccess(NetworkClient *user, LoginSuccessMessage *msg) {
    _manager->authenticationSuccess();
}

void ClientController::onServerError(NetworkClient *user, ErrorResponseMessage *msg) {
}

void ClientController::onCallRequest(NetworkClient *user, CallRequestMessage *msg) {
    _manager->requestCall(msg->pseudo, msg->host, msg->port);
}

void ClientController::onCallRefused(NetworkClient *user, CallRefusedMessage *msg) {
    _manager->callRefused();
}

void ClientController::onVoiceDataReceived(NetworkClient *user, VoiceDataMessage *msg) {
    _manager->addSampleAudio(msg->data);
}

void ClientController::onConnect(NetworkClient *client) {
    if (_manager->getImHost()) {
        client->send(ConnectionEtablishedMessage());
        _manager->callAccepted();
        _manager->callEtablish();
    }
}
