//
// Created by romain on 20/09/18.
//

#ifndef SERVER_NETWORKSESSION_H
#define SERVER_NETWORKSESSION_H


#include <boost/enable_shared_from_this.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/array.hpp>
#include <deque>
#include "Network.h"
#include "NetworkSessionHandler.h"
#include "BinaryReader.h"
#include "BinaryWriter.h"

class NetworkSession : public boost::enable_shared_from_this<NetworkSession> {
public:
    static ptr<NetworkSession> create(boost_io &io, NetworkSessionHandler &handler);

    void asyncAwaitPacket();
    session_id getId() const;
    tcp::socket &getSocket();

    void send(const boost::uint8_t *bytes, sizet length, bool safe);
    void send(std::vector<boost::uint8_t> const &bytes, bool safe);

private:
    NetworkSession(session_id id, boost_io &io, NetworkSessionHandler &handler);

    enum {
        PACKET_HEADER_BYTES = sizeof(header_type)
    };

    enum State {
        AWAIT_PACKET_LENGTH,
        AWAIT_PACKET_CONTENT
    };

    void asyncRead(sizet bytes);
    void onRead(const error_code &error);

    void asyncWrite();
    void onWritten(error_code const &error);

private:
    session_id _id;
    tcp::socket _socket;
    NetworkSessionHandler *_handler;
    State _state;
    std::vector<boost::uint8_t> _buffer;
    BinaryReader _reader;
    BinaryWriter _writer;
    std::deque<std::vector<boost::uint8_t>> _pending;
};


#endif //SERVER_NETWORKSESSION_H
