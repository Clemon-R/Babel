//
// Created by romain on 20/09/18.
//

#include "shared/Network.h"
#include "Handler.h"
#include "shared/NetworkServer.h"
#include "shared/NetworkConnector.h"
#include <boost/thread.hpp>
#include <boost/bind.hpp>

int main(int ac, char *args[]) {
    Handler handler(true);
    NetworkServer server(handler);
    boost::thread(boost::bind(&NetworkServer::run, &server));

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    Handler bis(false);
    NetworkConnector connector("127.0.0.1", server.getPort(), bis);
    connector.connect();
}