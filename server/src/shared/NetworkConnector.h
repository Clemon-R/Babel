//
// Created by romain on 30/09/18.
//

#ifndef SERVER_NETWORKCONNECTOR_H
#define SERVER_NETWORKCONNECTOR_H

#include <string>
#include <boost/thread.hpp>
#include "Network.h"
#include "NetworkSessionHandler.h"

class NetworkConnector {
public:
    NetworkConnector(std::string const &host, boost::uint16_t port, NetworkSessionHandler &handler);
    NetworkConnector(std::string const &host, std::string const &port, NetworkSessionHandler &handler);

    void connect(bool useThread = false);
    boost::thread &getThread();
    ptr<NetworkSession> &getSession();

private:
    void start();
    void onConnect(error_code const &error);

private:
    boost_io _io;
    tcp::resolver _resolver;
    tcp::resolver::query _query;
    tcp::resolver::iterator _endpoint;
    NetworkSessionHandler *_handler;
    ptr<NetworkSession> _session;
    boost::thread _thread;
};


#endif //SERVER_NETWORKCONNECTOR_H
