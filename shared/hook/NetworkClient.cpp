//
// Created by romain on 02/10/18.
//

#include "NetworkClient.h"
#include "NetworkProtocol.h"

NetworkClient::NetworkClient(ptr<NetworkSession> session)
        : _session(std::move(session)),
          _reader(),
          _writer()
{}


void NetworkClient::send(NetworkMessage const &message) {
    NetworkProtocol::serialize(message, _writer);
    _session->send(_writer.bytes());
}

std::unique_ptr<NetworkMessage> NetworkClient::read(char const *bytes, sizet length) {
    _reader.reset(bytes, length);
    return NetworkProtocol::deserialize(_reader);
}

void NetworkClient::kick() {
    _session->getSocket().close();
}

sizet NetworkClient::getId() const {
    return _session->getId();
}

ptr<NetworkSession> &NetworkClient::getSession() {
    return _session;
}
