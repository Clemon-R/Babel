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

    virtual void onConnect(ptr<NetworkSession> session, error_code const &error) const = 0;
    virtual void onReceived() const = 0;
    virtual void onSent() const = 0;
    virtual void onDisconnect() const = 0;
};

#endif //SERVER_NETWORKSESSIONHANDLER_H
