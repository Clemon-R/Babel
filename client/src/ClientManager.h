//
// Created by romain on 06/10/18.
//

#ifndef BABEL_CLIENTMANAGER_H
#define BABEL_CLIENTMANAGER_H


#include <shared/hook/HookNetworkConnector.h>

class ClientManager {
public:


private:

    HookNetworkConnector _connector;
    std::mutex locker;
};


#endif //BABEL_CLIENTMANAGER_H
