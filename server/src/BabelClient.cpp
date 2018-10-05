//
// Created by romain on 04/10/18.
//

#include "BabelClient.h"

BabelClient::BabelClient(ptr<NetworkSession> session)
        : NetworkClient(session)
{}

std::string &BabelClient::pseudo() {
    return _pseudo;
}
