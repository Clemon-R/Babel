//
// Created by romain on 05/10/18.
//

#ifndef SERVER_OUTCALLREQUESTMESSAGE_H
#define SERVER_OUTCALLREQUESTMESSAGE_H

#include "../shared/hook/NetworkMessage.h"

struct CallRequestMessage : NetworkMessage {
    static opcode constexpr OPCODE = 6;

    std::string pseudo;
    std::string host;
    boost::uint16_t port;

    CallRequestMessage() : NetworkMessage(OPCODE) {}
    CallRequestMessage(std::string const &pseudo_, std::string const &host_, boost::uint16_t port_)
            : NetworkMessage(OPCODE),
              pseudo(pseudo_),
              host(host_),
              port(port_)
    {}
    CallRequestMessage(std::string const &pseudo_, boost::uint16_t port_)
            : NetworkMessage(OPCODE),
              pseudo(pseudo_),
              host(),
              port(port_)
    {}

    void serialize(BinaryWriter &writer) const override {
        writer & pseudo & host & port;
    }

    void deserialize(BinaryReader &reader) override {
        reader & pseudo & host & port;
    }

    std::ostream &dump(std::ostream &o) const override {
        return o << "CallRequestMessage(pseudo=" << &pseudo[0] << ", host=" << &host[0] << "port=" << port << ")";
    }
};

#endif //SERVER_OUTCALLREQUESTMESSAGE_H
