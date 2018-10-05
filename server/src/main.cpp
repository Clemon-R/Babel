//
// Created by romain on 20/09/18.
//

#include "../../shared/Network.h"
#include "../../shared/NetworkServer.h"
#include "../../shared/NetworkConnector.h"
#include "BabelServer.h"
#include "BabelController.h"
#include "client/ServerController.h"
#include <boost/thread.hpp>
#include <boost/bind.hpp>

void client() {
    ServerController controller;
    BabelConnector connector("127.0.0.1", 4242, controller);
    controller.setConnector(connector);

    connector.connect();
}

int main(int ac, char *args[]) {
    if (ac == 2) {
        client();
        return 0;
    }
    BabelController controller;
    BabelServer server(controller, 4242);
    controller.setServer(server);

    server.run();
    return 0;
}