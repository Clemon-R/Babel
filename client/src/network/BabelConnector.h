//
// Created by raphael on 06/10/18.
//

#ifndef BABEL_BABELCONNECTOR_H
#define BABEL_BABELCONNECTOR_H


#include "shared/hook/HookNetworkConnector.h"
#include "ClientController.h"

class BabelConnector : public HookNetworkConnector {
public:
    BabelConnector(std::string const &host, boost::uint16_t port);
    BabelConnector(std::string const &host, std::string const &port);


private:
    ClientController _controller;
};


#endif //BABEL_BABELCONNECTOR_H
