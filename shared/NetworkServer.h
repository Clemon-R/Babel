//
// Created by romain on 20/09/18.
//

#ifndef SERVER_NETWORKSERVER_H
#define SERVER_NETWORKSERVER_H

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <unordered_map>
#include <boost/thread.hpp>
#include "NetworkSession.h"
#include "Network.h"
#include "NetworkSessionHandler.h"

class NetworkServer {
public:
    enum {
        RANDOM_PORT = 0
    };

    explicit NetworkServer(NetworkSessionHandler *handler, boost::uint16_t port = RANDOM_PORT);

    virtual void run(bool useThread);
    boost::uint16_t getPort() const;
    boost::thread &getThread();

private:
    void asyncAccept();
    void onAccept(ptr<NetworkSession> session, error_code const &error);

private:
    boost_io _io;
    tcp::acceptor _acceptor;
    NetworkSessionHandler *_handler;
    boost::thread _thread;
};


#endif //SERVER_NETWORKSERVER_H
