//
// Created by romain on 20/09/18.
//

#include "NetworkServer.h"
#include "NetworkSession.h"

NetworkServer::NetworkServer(NetworkSessionHandler &handler, boost::uint16_t port)
        : _io(),
          _acceptor(_io, tcp::endpoint(tcp::v4(), port)),
          _handler(&handler)
{}

void NetworkServer::run() {
    asyncAccept();
    _io.run();
}

boost::uint16_t NetworkServer::getPort() const {
    return _acceptor.local_endpoint().port();
}

void NetworkServer::asyncAccept() {
    ptr<NetworkSession> session = NetworkSession::create(_io, *_handler);

    auto handler = boost::bind(&NetworkServer::onAccept, this, session, boost::asio::placeholders::error);

    _acceptor.async_accept(session->getSocket(), handler);
}

void NetworkServer::onAccept(ptr<NetworkSession> session, const error_code &error) {
    if (!error) {
        _handler->onConnect(session);
        session->asyncAwaitPacket();
    }
    asyncAccept();
}
