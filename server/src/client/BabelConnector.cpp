//
// Created by romain on 04/10/18.
//

#include "BabelConnector.h"

BabelConnector::BabelConnector(std::string const &host, std::string const &port, NetworkController &controller)
        : HookNetworkConnector(host, port, controller)
{}

BabelConnector::BabelConnector(std::string const &host, boost::uint16_t port, NetworkController &controller)
        : HookNetworkConnector(host, port, controller)
{}
