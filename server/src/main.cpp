//
// Created by romain on 20/09/18.
//

#include "shared/Network.h"
#include "shared/NetworkServer.h"
#include "shared/NetworkConnector.h"
#include "BabelServer.h"
#include "BabelController.h"
#include <boost/thread.hpp>
#include <boost/bind.hpp>

int main(int ac, char *args[]) {
    BabelController controller;
    BabelServer server(controller);
    controller.setServer(server);

    server.run();
}