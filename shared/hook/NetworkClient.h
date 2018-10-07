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
    virtual ~NetworkClient() {};

    virtual void send(NetworkMessage &&message, bool safe = false);
    virtual void send(NetworkMessage const &message, bool safe = false);
    virtual std::unique_ptr<NetworkMessage> read(const boost::uint8_t *bytes, sizet length);

    void kick();
    virtual sizet getId() const;
    ptr<NetworkSession> &getSession();

private:
    ptr<NetworkSession> _session;
    BinaryReader _reader;
    BinaryWriter _writer;
};


#endif //SERVER_ANETWORKCLIENT_H
