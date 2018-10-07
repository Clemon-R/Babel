//
// Created by romain on 05/10/18.
//

#ifndef SERVER_ERRORRESPONSEMESSAGE_H
#define SERVER_ERRORRESPONSEMESSAGE_H

#include "../shared/Util.h"
#include "../shared/hook/NetworkMessage.h"

struct ErrorResponseMessage : NetworkMessage {
    static opcode constexpr OPCODE = 8;

    std::string what;

    ErrorResponseMessage() : NetworkMessage(OPCODE) {}
    ErrorResponseMessage(std::string &&what) : NetworkMessage(OPCODE),
              what(what)
    {}

    void serialize(BinaryWriter &writer) const override {
        writer & what;
    }

    void deserialize(BinaryReader &reader) override {
        reader & what;
    }

    std::ostream &dump(std::ostream &o) const override {
        return o << "ErrorResponseMessage(" << util::dump("what", what) << ")";
    }
};

#endif //SERVER_ERRORRESPONSEMESSAGE_H
