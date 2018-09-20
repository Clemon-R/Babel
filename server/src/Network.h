//
// Created by romain on 20/09/18.
//

#ifndef SERVER_NETWORK_H
#define SERVER_NETWORK_H

#include <boost/asio.hpp>

template<class T>
using ptr = boost::shared_ptr<T>;

using session_id = unsigned long;
using error_code = boost::system::error_code;
using boost_io = boost::asio::io_service;
using boost::asio::ip::tcp;

#endif //SERVER_NETWORK_H
