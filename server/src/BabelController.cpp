//
// Created by romain on 04/10/18.
//

#include "../../protocol/DelContactMessage.h"
#include "BabelController.h"
#include "../../protocol/HelloConnectMessage.h"
#include "../../protocol/AddContactMessage.h"
#include "../../protocol/ErrorResponseMessage.h"
#include "../../protocol/LoginSuccessMessage.h"
#include "../../protocol/LoginFailedMessage.h"

void BabelController::onConnect(NetworkClient *client) {
    client->send(HelloConnectMessage());
}

void BabelController::onDisconnect(NetworkClient *client, error_code const &error) {
    auto user = dynamic_cast<BabelUser *>(client);

    _server->sendToAll(user, DelContactMessage(user->pseudo()));
}

void BabelController::onCallRequest(BabelUser *client, CallRequestMessage *msg) {
    BabelUser *called = _server->find(msg->pseudo);

    if (called == nullptr) {
        client->send(ErrorResponseMessage("requested username not found"));
        return;
    }
    called->send(CallRequestMessage(client->pseudo(), msg->host, msg->port));
}

void BabelController::onLogin(BabelUser *client, LoginMessage *msg) {
    BabelUser *exist = _server->find(msg->pseudo);

    if (exist == nullptr) {
        client->send(LoginFailedMessage("username already used"));
        return;
    }

    std::vector<std::string> users;
    for (auto &keyset: _server->getClients()) {
        auto user = dynamic_cast<BabelUser *>(keyset.second.get());
        users.push_back(user->pseudo());
    }

    client->pseudo() = msg->pseudo;
    client->send(LoginSuccessMessage());
    client->send(AddContactMessage(users));
    _server->sendToAll(client, AddContactMessage(client->pseudo()));
}

void BabelController::onCallRefused(BabelUser *client, CallRefusedMessage *msg) {
    BabelUser *caller = _server->find(msg->pseudo);

    if (caller == nullptr)
        return;

    caller->send(CallRefusedMessage(client->pseudo()));
}
