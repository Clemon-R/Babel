//
// Created by romain on 30/09/18.
//

#include "NetworkConnector.h"
#include "NetworkSession.h"
#include <boost/bind.hpp>

NetworkConnector::NetworkConnector(std::string const &host, boost::uint16_t port, NetworkSessionHandler *handler)
        : _io(),
          _resolver(_io),
          _query(host, std::to_string(port)),
          _endpoint(_resolver.resolve(_query)),
          _handler(handler),
          _session(),
          _thread()
{}

NetworkConnector::NetworkConnector(std::string const &host, std::string const &port, NetworkSessionHandler *handler)
        : _io(),
          _resolver(_io),
          _query(host, port),
          _endpoint(_resolver.resolve(_query)),
          _handler(handler),
          _session(),
          _thread()
{}

void NetworkConnector::connect(bool useThread) {
    start();

    if (useThread)
        _thread = boost::thread(boost::bind(&boost::asio::io_service::run, &_io));
    else
        _io.run();
}

void NetworkConnector::start() {
    _session = NetworkSession::create(_io, *_handler);

    auto handler = boost::bind(&NetworkConnector::onConnect, this, boost::asio::placeholders::error);
    boost::asio::async_connect(_session->getSocket(), _endpoint, handler);
}

void NetworkConnector::onConnect(error_code const &error) {
    if (error)
        throw std::runtime_error("NetworkConnector: can't connect");
    _handler->onConnect(_session);
    _session->asyncAwaitPacket();
}

boost::thread &NetworkConnector::getThread() {
    return _thread;
}

ptr<NetworkSession> &NetworkConnector::getSession() {
    return _session;
}
