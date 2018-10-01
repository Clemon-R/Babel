//
// Created by romain on 22/09/18.
//

#ifndef SERVER_HANDLER_H
#define SERVER_HANDLER_H


#include "shared/NetworkSessionHandler.h"

class Handler : public NetworkSessionHandler {
public:
    Handler(bool serv) : _serv(serv) {}
    void onConnect(ptr<NetworkSession> session) const override;
    void onReceived(ptr<NetworkSession> session, const char *data, sizet size) const override;
    void onSent(ptr<NetworkSession> session, const char *data, sizet size) const override;
    void onDisconnect(ptr<NetworkSession> session, error_code const &error) const override;

private:
    bool _serv;
};


#endif //SERVER_HANDLER_H
