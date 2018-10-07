//
// Created by romain on 30/09/18.
//

#include "NetworkConnector.h"
#include "NetworkSession.h"
#include <boost/bind.hpp>

NetworkConnector::NetworkConnector(NetworkSessionHandler *handler)
        : _io(),
          _handler(handler),
          _session(),
          _thread()
{}

void NetworkConnector::connect(std::string const &host, std::string const &port, bool useThread) {
    _io.reset(new boost_io());
    _session = NetworkSession::create(*_io, *_handler);

    tcp::resolver resolver(*_io);
    tcp::resolver::query query(host, port);
    tcp::resolver::iterator endpoint(resolver.resolve(query));

    auto handler = boost::bind(&NetworkConnector::onConnect, this, boost::asio::placeholders::error);
    boost::asio::async_connect(_session->getSocket(), endpoint, handler);

    if (useThread)
        _thread = boost::thread(boost::bind(&boost::asio::io_service::run, _io.get()));
    else
        _io->run();
}

void NetworkConnector::connect(std::string const &host, boost::uint16_t port, bool useThread) {
    connect(host, std::to_string(port), useThread);
}


void NetworkConnector::onConnect(error_code const &error) {
    if (error)
        throw std::runtime_error("NetworkConnector: can't connectToServer");
    _handler->onConnect(_session);
    _session->asyncAwaitPacket();
}

boost::thread &NetworkConnector::getThread() {
    return _thread;
}

ptr<NetworkSession> &NetworkConnector::getSession() {
    return _session;
}
