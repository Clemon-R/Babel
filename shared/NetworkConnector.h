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
    NetworkConnector(NetworkSessionHandler *handler);

    virtual void connect(std::string const &host, std::string const &port, bool useThread);
    virtual void connect(std::string const &host, boost::uint16_t port, bool useThread);

    boost::thread &getThread();
    ptr<NetworkSession> &getSession();

private:
    void onConnect(error_code const &error);

private:
    std::unique_ptr<boost_io> _io;
    NetworkSessionHandler *_handler;
    ptr<NetworkSession> _session;
    boost::thread _thread;
};


#endif //SERVER_NETWORKCONNECTOR_H
