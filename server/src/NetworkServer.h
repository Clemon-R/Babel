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
#include "Network.h"
#include "NetworkSessionHandler.h"

class NetworkServer {
public:
    NetworkServer(unsigned short port, NetworkSessionHandler &handler);

    void run();

private:
    void asyncAccept();
    void onAccept(ptr<NetworkSession> session, error_code error);

private:
    boost_io _io;
    tcp::acceptor _acceptor;
    NetworkSessionHandler *_handler;
};


#endif //SERVER_NETWORKSERVER_H
