//
// Created by romain on 04/10/18.
//

#ifndef SERVER_BABELCONNECTOR_H
#define SERVER_BABELCONNECTOR_H


#include "../shared/Network.h"
#include "../shared/hook/HookNetworkConnector.h"

class BabelConnector : public HookNetworkConnector {
public:
    BabelConnector(std::string const &host, boost::uint16_t port, NetworkController &controller);
    BabelConnector(std::string const &host, std::string const &port, NetworkController &controller);

private:

};


#endif //SERVER_BABELCONNECTOR_H
