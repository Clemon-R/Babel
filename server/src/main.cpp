//
// Created by romain on 20/09/18.
//

#include "../../shared/Network.h"
#include "../../shared/NetworkServer.h"
#include "../../shared/NetworkConnector.h"
#include "BabelServer.h"
#include "BabelController.h"
#include "client/ServerController.h"
#include "../../protocol/UpdateContactMessage.h"
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
    } else if (ac == 3) {
        std::vector<std::string> a;
        a.emplace_back("lol");
        a.emplace_back("petite pute");
        UpdateContactMessage msg(a, a);

        BinaryWriter writer;
        msg.serialize(writer);
        for (sizet i=0; i < writer.bytes().size(); ++i)
            printf("%d.", writer.bytes()[i]);
        printf("\n");
        BinaryReader reader;
        reader.reset(&writer.bytes()[0], writer.bytes().size());
        msg.deserialize(reader);
        std::cout << msg;
        return 0;
    }
    BabelController controller;
    BabelServer server(controller, 4242);
    controller.setServer(server);

    server.run();
    return 0;
}