//
// Created by romain on 20/09/18.
//

#include <boost/make_shared.hpp>
#include "NetworkSession.h"

NetworkSession::NetworkSession(session_id id, boost_io &io, NetworkSessionHandler &handler)
        : _id(id),
          _socket(io),
          _handler(&handler)
{}

ptr<NetworkSession> NetworkSession::create(boost_io &io, NetworkSessionHandler &handler) {
    static session_id id = 0;

    return ptr<NetworkSession>(new NetworkSession(++id, io, handler)); //make_shared<?> requires public constructor of NetworkSession
}

session_id NetworkSession::getId() const {
    return _id;
}

tcp::socket &NetworkSession::getSocket() {
    return _socket;
}
