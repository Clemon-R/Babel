//
// Created by romain on 20/09/18.
//

#ifndef SERVER_NETWORK_H
#define SERVER_NETWORK_H

#include <boost/asio.hpp>

using sizet = boost::uintmax_t;
using ssizet = boost::intmax_t;


template<class T>
using ptr = boost::shared_ptr<T>;

using session_id = sizet;
using error_code = boost::system::error_code;
using boost_io = boost::asio::io_service;
using boost::asio::ip::tcp;
using header_type = boost::uint64_t;

#endif //SERVER_NETWORK_H
