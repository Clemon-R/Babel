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
    //TODO: disconnected from the server (error.what() = reason )
    if ((!_manager->getImHost() && _manager->getIsCalling()) || (_manager->isHostClient(client->getId()) && _manager->getHostClients() == 1)) {
        _manager->endOfCall();
    }
    if (_manager->isHostClient(client->getId())) {
        //TODO: il reste des gens dans la call
    }
}

void ClientController::onContactReady(NetworkClient *user, ConnectionEtablishedMessage *msg) {
    _manager->callEtablish();
    //TODO: connected to the contact in P2P
    // TU peux commencer à sendToServer des VoiceDataMessage depuis là
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

    /** TODO:   supprimer les contacts reçus
     *          refresh l'UI
     *          penser à quitter la requête d'appel si le mec essaie d'appeler un mec qui est
     *          dans cette liste
     **/
}

void ClientController::onLoginFailed(NetworkClient *user, LoginFailedMessage *msg) {
    _manager->authenticationFailed();
}

void ClientController::onLoginSuccess(NetworkClient *user, LoginSuccessMessage *msg) {
    _manager->authenticationSuccess();
}

void ClientController::onServerError(NetworkClient *user, ErrorResponseMessage *msg) {
    msg->what;
    //TODO: erreur que tu reçois quand tu essaies de call quelqu'un qui n'est plus connecté
    //      ca ne devrait jamais arriver, sauf si le client bidouille les packets
    //      quoi que ça pourrait arriver si le mec appelle un contact en même temps que
    //      celui ci se deconnecte
}

void ClientController::onCallRequest(NetworkClient *user, CallRequestMessage *msg) {
    _manager->requestCall(msg->pseudo, msg->host, msg->port);
}

void ClientController::onCallRefused(NetworkClient *user, CallRefusedMessage *msg) {
    _manager->callRefused();

    //TODO: raffraichir l'UI, call refusée
}

void ClientController::onVoiceDataReceived(NetworkClient *user, VoiceDataMessage *msg) {
    _manager->addSampleAudio(msg->data);


    //TODO: C'est ici que tu reçois la data audio, faut les faire écouter au client
}

void ClientController::onConnect(NetworkClient *client) {
    if (_manager->getImHost()) {
        client->send(ConnectionEtablishedMessage());
        _manager->callAccepted();
        _manager->callEtablish();
    }
}
