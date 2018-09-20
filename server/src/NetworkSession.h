//
// Created by romain on 20/09/18.
//

#ifndef SERVER_NETWORKSESSION_H
#define SERVER_NETWORKSESSION_H


#include <boost/enable_shared_from_this.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <deque>
#include "Network.h"
#include "NetworkSessionHandler.h"

class NetworkSession : public boost::enable_shared_from_this<NetworkSession> {
public:
    static ptr<NetworkSession> create(boost_io &io, NetworkSessionHandler &handler);

    /**
     * TODO:
     *  * read / write asynchrone
     */

    session_id getId() const;
    tcp::socket &getSocket();

private:
    NetworkSession(session_id id, boost_io &io, NetworkSessionHandler &handler);

private:
    session_id _id;
    tcp::socket _socket;
    NetworkSessionHandler *_handler;
};


#endif //SERVER_NETWORKSESSION_H
