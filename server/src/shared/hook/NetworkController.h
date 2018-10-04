//
// Created by romain on 02/10/18.
//

#ifndef SERVER_NETWORKCONTROLLER_H
#define SERVER_NETWORKCONTROLLER_H

#include <unordered_map>
#include <iostream>
#include "../Network.h"
#include "NetworkClient.h"

using handler_t = std::function<void (NetworkClient *, NetworkMessage *)>;
using handlers_t = std::unordered_map<sizet, handler_t>;

template <typename T, typename V, typename X>
using typed_handler_t = void (T::*)(X *, V *);

template<class D>
class NetworkController {
public:

    virtual void init() {
        defineMessageHandlers(_handlers);
    }

    void parseMessage(NetworkClient *client, NetworkMessage *msg) {
        try {
            _handlers.at((msg->getOpcode()))(client, msg);
        } catch (std::exception &e) {
            std::cerr << "no handler found for protocol id " << msg->getOpcode() << std::endl;
            throw std::runtime_error(e.what());
        }
    }

protected:

    virtual void defineMessageHandlers(handlers_t &handlers) = 0;
    virtual void onConnect(D *client) = 0;
    virtual void onDisconnect(D *client, error_code &error) = 0;

    template <typename T,typename V>
    handler_t handler(T &holder, typed_handler_t<T, V, D> addr) {
        return [&holder, addr](D *client, NetworkMessage *msg) mutable {
            (holder.*addr)(client, dynamic_cast<V *>(msg));
        };
    };

private:

    handlers_t _handlers;
};

#endif //SERVER_NETWORKCONTROLLER_H
