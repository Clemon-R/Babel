//
// Created by romain on 04/10/18.
//

#ifndef SERVER_BABELCLIENT_H
#define SERVER_BABELCLIENT_H


#include "shared/hook/NetworkClient.h"

class BabelClient: public NetworkClient {
public:
    explicit BabelClient(ptr<NetworkSession> session);

    std::string &pseudo();

private:
    std::string _pseudo;
};


#endif //SERVER_BABELCLIENT_H
