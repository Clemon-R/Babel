//
// Created by romain on 06/10/18.
//

#include "ClientManager.h"

ClientManager::ClientManager()
        : _controller(this),
          _connector(_controller),
          _server(_controller),
          _locker()
{}
