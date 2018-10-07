//
// Created by romain on 20/09/18.
//

#ifndef SERVER_NETWORKSESSIONHANDLER_H
#define SERVER_NETWORKSESSIONHANDLER_H

#include "Network.h"

class NetworkSession;

class NetworkSessionHandler {
public:
    virtual ~NetworkSessionHandler() = default;

    virtual void onConnect(ptr<NetworkSession> session) const = 0;
    virtual void onReceived(ptr<NetworkSession> session, const boost::uint8_t *data, sizet size) const = 0;
    virtual void onSent(ptr<NetworkSession> session, const boost::uint8_t *data, sizet size) const = 0;
    virtual void onDisconnect(ptr<NetworkSession> session, error_code const &error) const = 0;
};

#endif //SERVER_NETWORKSESSIONHANDLER_H
