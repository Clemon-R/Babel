//
// Created by romain on 20/09/18.
//

#include <boost/make_shared.hpp>
#include <boost/asio/error.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include "NetworkSession.h"

NetworkSession::NetworkSession(session_id id, boost_io &io, NetworkSessionHandler &handler)
        : _id(id),
          _socket(io),
          _handler(&handler),
          _state(AWAIT_PACKET_LENGTH),
          _buffer(),
          _reader(),
          _writer(),
          _pending()
{}

ptr<NetworkSession> NetworkSession::create(boost_io &io, NetworkSessionHandler &handler) {
    static session_id id = 0;

    return ptr<NetworkSession>(new NetworkSession(++id, io, handler)); //make_shared<?> requires public constructor of NetworkSession
}

void NetworkSession::asyncAwaitPacket() {
    _state = AWAIT_PACKET_LENGTH;
    asyncRead(PACKET_HEADER_BYTES);
}

void NetworkSession::onRead(const error_code &error) {
    if (error) {
        onerror:
        _handler->onDisconnect(shared_from_this(), error);
        _socket.close();
        return;
    }

    switch (_state) {
        case AWAIT_PACKET_LENGTH: {
            _state = AWAIT_PACKET_CONTENT;

            std::string s(_buffer.begin(), _buffer.end());
            header_type packet_size;
            _reader.reset(&s[0], s.size());

            try {
                _reader & packet_size;
            } catch (std::exception &e) {
                _socket.close();
                return;
            }

            asyncRead(packet_size);
            break;
        }
        case AWAIT_PACKET_CONTENT: {
            _state = AWAIT_PACKET_LENGTH;

            _handler->onReceived(shared_from_this(), &_buffer[0], _buffer.size());
            asyncAwaitPacket();
            break;
        }
        default:
            std::cerr << "NetworkSession::onRead(): unexpected state (UNDEFINED)" << std::endl;
            goto onerror;
    }
}

void NetworkSession::asyncRead(sizet bytes) {
    _buffer.clear();
    _buffer.resize(bytes);
    auto handler = boost::bind(&NetworkSession::onRead, shared_from_this(), boost::asio::placeholders::error);
    boost::asio::async_read(_socket, boost::asio::buffer(_buffer), boost::asio::transfer_exactly(bytes), handler);
}

session_id NetworkSession::getId() const {
    return _id;
}

tcp::socket &NetworkSession::getSocket() {
    return _socket;
}

void NetworkSession::send(char const *bytes, sizet length) {
    _pending.emplace_back(bytes, bytes + length);
    if (_pending.empty())
        asyncWrite();
}

void NetworkSession::send(std::vector<char> const &bytes) {
    _pending.push_back(bytes);
    if (_pending.empty())
        asyncWrite();
}

void NetworkSession::asyncWrite() {
    auto &next = _pending.front();
    auto &bytes = _writer.bytes();

    _writer.reset();
    _writer & ((header_type) next.size());
    bytes.insert(bytes.end(), next.begin(), next.end());

    auto handler = boost::bind(&NetworkSession::onWritten, shared_from_this(), boost::asio::placeholders::error);
    boost::asio::async_write(_socket, boost::asio::buffer(bytes, bytes.size()), handler);
}

void NetworkSession::onWritten(error_code const &error) {
    auto &sent = _pending.front();
    _handler->onSent(shared_from_this(), &sent[0], sent.size());
    _pending.pop_front();

    if (!_pending.empty())
        asyncWrite();
}
