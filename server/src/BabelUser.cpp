//
// Created by romain on 04/10/18.
//

#include "BabelUser.h"

BabelUser::BabelUser(ptr<NetworkSession> session)
        : NetworkClient(session)
{}

std::string &BabelUser::pseudo() {
    return _pseudo;
}
