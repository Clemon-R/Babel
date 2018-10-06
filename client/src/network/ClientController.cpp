//
// Created by romain on 06/10/18.
//

#include <protocol/LoginMessage.h>
#include "ClientController.h"

void ClientController::onServerReady(NetworkClient *user, HelloConnectMessage *msg) {
    user->send(LoginMessage("username"));
}

void ClientController::onDisconnect(NetworkClient *client, error_code const &error) {
    //TODO: disconnected from the server (error.what() = reason )
}

void ClientController::onContactReady(NetworkClient *user, ConnectionEtablishedMessage *msg) {
    //TODO: connected to the contact in P2P
    // TU peux commencer à send des VoiceDataMessage depuis là
}

void ClientController::onNewContact(NetworkClient *user, AddContactMessage *msg) {
    msg->newClients; //list of strings

    /** TODO:   stoquer tous les contacts (on identifie les client par leur pseudo
     *          le pseudo est bien unique, l'utilise comme ID en gros
     *          refresh l'uI
     **/
}

void ClientController::onDisconnectedContact(NetworkClient *user, DelContactMessage *msg) {
    msg->delClients; //list of strings

    /** TODO:   supprimer les contacts reçus
     *          refresh l'UI
     *          penser à quitter la requête d'appel si le mec essaie d'appeler un mec qui est
     *          dans cette liste
     **/
}

void ClientController::onLoginFailed(NetworkClient *user, LoginFailedMessage *msg) {
    msg->reason;
    //TODO: pseudo déjà utilisé
}

void ClientController::onLoginSuccess(NetworkClient *user, LoginSuccessMessage *msg) {
    //TODO: login accepté, tu peux le mettre sur la page de contacts
}

void ClientController::onServerError(NetworkClient *user, ErrorResponseMessage *msg) {
    msg->what;
    //TODO: erreur que tu reçois quand tu essaies de call quelqu'un qui n'est plus connecté
    //      ca ne devrait jamais arriver, sauf si le client bidouille les packets
    //      quoi que ça pourrait arriver si le mec appelle un contact en même temps que
    //      celui ci se deconnecte
}

void ClientController::onCallRequest(NetworkClient *user, CallRequestMessage *msg) {
    msg->host; //host ip
    msg->port;
    msg->pseudo; //caller
    //TODO: appel entrant, stoquer les infos de connexion
    //      si le mec refuse l'appel, envoyer un RefusedCallMessage(caller)
    //      si il accepte, tu te connecte au host:port
}

void ClientController::onCallRefused(NetworkClient *user, CallRefusedMessage *msg) {
    msg->pseudo; //contact appelé qui a refusé

    //TODO: raffraichir l'UI, call refusée
}

void ClientController::onVoiceDataReceived(NetworkClient *user, VoiceDataMessage *msg) {
    msg->data; //list de char (faut vérifier qu'un byte dépasse pas 127
                //si c'est le cas je dois passer le buffer en unsigned char


    //TODO: C'est ici que tu reçois la data audio, faut les faire écouter au client
}
