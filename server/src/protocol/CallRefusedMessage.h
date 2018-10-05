//
// Created by romain on 05/10/18.
//

#ifndef SERVER_REFUSECALLREQUEST_H
#define SERVER_REFUSECALLREQUEST_H

#include "../shared/hook/NetworkMessage.h"

struct CallRefusedMessage : NetworkMessage {
    static opcode constexpr OPCODE = 9;

    std::string pseudo;

    CallRefusedMessage() : NetworkMessage(OPCODE) {}
    CallRefusedMessage(std::string &&pseudo_) : NetworkMessage(OPCODE),
              pseudo(pseudo_)
    {}

    void serialize(BinaryWriter &writer) const override {
        writer & pseudo;
    }

    void deserialize(BinaryReader &reader) override {
        reader & pseudo;
    }

    std::ostream &dump(std::ostream &o) const override {
        return o << "CallRefusedMessage(pseudo=" << &pseudo[0] << ")";
    }
};

#endif //SERVER_REFUSECALLREQUEST_H
