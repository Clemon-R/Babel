//
// Created by raphael on 06/10/18.
//

#include "BabelConnector.h"

BabelConnector::BabelConnector(std::string const &host, boost::uint16_t port)
        : HookNetworkConnector(host, port, _controller)
{}

BabelConnector::BabelConnector(std::string const &host, std::string const &port)
        : HookNetworkConnector(host, port, _controller)
{}
