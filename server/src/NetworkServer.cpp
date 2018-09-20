//
// Created by romain on 20/09/18.
//

#include "NetworkServer.h"
#include "NetworkSession.h"

NetworkServer::NetworkServer(unsigned short port, NetworkSessionHandler &handler)
        : _io(),
          _acceptor(_io, tcp::endpoint(tcp::v4(), port)),
          _handler(&handler)
{}

void NetworkServer::run() {
    asyncAccept();
    _io.run();
}

void NetworkServer::asyncAccept() {
    ptr<NetworkSession> session = NetworkSession::create(_io, *_handler);

    auto handler = boost::bind(&NetworkServer::onAccept, this, session, boost::asio::placeholders::error);

    _acceptor.async_accept(session->getSocket(), handler);
}

void NetworkServer::onAccept(ptr<NetworkSession> client, error_code error) {
    if (!error) {
        //TODO: async session read
        _handler->onConnect(std::move(client), error);
    }
    asyncAccept();
}