//
// Created by romain on 02/10/18.
//

#ifndef SERVER_ANETWORKCLIENT_H
#define SERVER_ANETWORKCLIENT_H


#include <utility>
#include "../NetworkSession.h"
#include "NetworkMessage.h"

class NetworkClient {
public:
    explicit NetworkClient(ptr<NetworkSession> session);

    virtual void send(NetworkMessage const &message);
    virtual std::unique_ptr<NetworkMessage> read(char const *bytes, sizet length);

    void kick();
    virtual sizet getId() const;
    ptr<NetworkSession> &getSession();

private:
    ptr<NetworkSession> _session;
    BinaryReader _reader;
    BinaryWriter _writer;
};


#endif //SERVER_ANETWORKCLIENT_H
