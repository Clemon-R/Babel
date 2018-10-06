//
// Created by romain on 06/10/18.
//

#include "ClientManager.h"
#include <algorithm>

ClientManager::ClientManager()
        : _controller(this),
          _connector(_controller),
          _server(_controller),
          _locker(),
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
}

void ClientManager::delContact(std::string const &contact) {
    lock_t lock(_locker);

    std::remove_if(_contacts.begin(),_contacts.end(), [](std::string &s) { s == contact; });
}

void ClientManager::send(NetworkMessage const &message) {
    lock_t lock(_locker);

    _connector.getClient()->send(message);
}
