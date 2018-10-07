//
// Created by romain on 20/09/18.
//

#include "../../shared/Network.h"
#include "../../shared/NetworkServer.h"
#include "../../shared/NetworkConnector.h"
#include "BabelServer.h"
#include "BabelController.h"
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

int main(int ac, char *args[]) {
    boost::uint16_t port = NetworkServer::RANDOM_PORT;

    if (ac >= 2) {
        port = (boost::uint16_t) atoi(args[1]);

        if (port == 0) {
            std::cerr << *args << ": invalid port" << std::endl;
            std::cerr << "USAGE: " << *args << " [:port number]" << std::endl;
            return 1;
        }
    } else
        std::cout << "[babel-server] no port specified, random port will be used" << std::endl;

    BabelController controller;
    try {
        BabelServer server(controller, port);
        controller.setServer(server);

        server.run(true);
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        std::cout << "[babel-server] listening on port " << server.getPort() << std::endl;
        std::cout << "[babel-server] awaiting connections..." << std::endl;
        server.getThread().join();
    } catch (std::exception &e) {
        std::cerr << *args << "an error has occurred (system port?): " << e.what() << std::endl;
        return 1;
    }
    return 0;
}