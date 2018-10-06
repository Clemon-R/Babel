//
// Created by romain on 06/10/18.
//

#include "ClientManager.h"
#include <algorithm>
#include <client/src/forms/livewindow.h>
#include <client/src/network/ClientController.h>
#include <protocol/LoginMessage.h>
#include "ui_livewindow.h"

ClientManager::ClientManager(LiveWindow *ui, const std::string &username)
        : _controller(new ClientController(this)),
          _connector(*_controller),
          _server(*_controller),
          _locker(),
          _ui(ui),
          _username(username),
          _contacts()
{}

void ClientManager::startHost() {
    lock_t lock(_locker);

    _server.run(true);
}

boost::uint16_t ClientManager::getPort() {
    lock_t lock(_locker);

    return _server.getPort();
}

void ClientManager::connect(std::string const &host, uint16_t port) {
    lock_t lock(_locker);

    _connector.connect(host, port, true);
}

void ClientManager::addContact(std::string const &contact) {
    lock_t lock(_locker);

    _contacts.push_back(contact);
    _ui->insertListData(contact);
}

void ClientManager::delContact(std::string const &contact) {
    lock_t lock(_locker);

    std::remove_if(_contacts.begin(),_contacts.end(), [&contact](std::string &s) { return s == contact; });
}

void ClientManager::send(NetworkMessage const &message) {
    lock_t lock(_locker);

    _connector.getClient()->send(message);
}

std::vector<std::string> const &ClientManager::getContacts() const {
    return _contacts;
}

void ClientManager::connectSuccess() {
    _ui->displayConnectSuccess();
}

void ClientManager::authenticationSuccess() {
    _ui->displayAuthenticationSuccess();
}

void ClientManager::authenticationFailed() {
    _ui->displayAuthenticationFailed();
}

void ClientManager::authentication(){
    _ui->displayAuthentication();
    send(LoginMessage(_username));
}
