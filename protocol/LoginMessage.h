//
// Created by romain on 04/10/18.
//

#ifndef SERVER_LOGINMESSAGE_H
#define SERVER_LOGINMESSAGE_H

#include "../shared/hook/NetworkMessage.h"

struct LoginMessage : NetworkMessage {
    static opcode constexpr OPCODE = 2;

    std::string pseudo;

    LoginMessage() : NetworkMessage(OPCODE) {}
    LoginMessage(const std::string &pseudo_) : NetworkMessage(OPCODE),
              pseudo(pseudo_)
    {}

    void serialize(BinaryWriter &writer) const override {
        writer & pseudo;
    }

    void deserialize(BinaryReader &reader) override {
        reader & pseudo;
    }

    std::ostream &dump(std::ostream &o) const override {
        return o << "LoginMessage(pseudo=" << pseudo << ")";
    }
};

#endif //SERVER_LOGINMESSAGE_H
