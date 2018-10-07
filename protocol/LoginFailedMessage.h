//
// Created by romain on 04/10/18.
//

#ifndef SERVER_LOGINFAILEDMESSAGE_H
#define SERVER_LOGINFAILEDMESSAGE_H

#include "../shared/hook/NetworkMessage.h"
#include "../shared/Util.h"

struct LoginFailedMessage : NetworkMessage {
    static opcode constexpr OPCODE = 4;

    std::string reason;

    LoginFailedMessage() : NetworkMessage(OPCODE) {}
    LoginFailedMessage(std::string &&reason_) : NetworkMessage(OPCODE),
            reason(reason_)
    {}

    void serialize(BinaryWriter &writer) const override {
        writer & reason;
    }

    void deserialize(BinaryReader &reader) override {
        reader & reason;
    }

    std::ostream &dump(std::ostream &o) const override {
        return o << "LoginFailedMessage(" << util::dump("reason", reason) <<")";
    }
};

#endif //SERVER_LOGINFAILEDMESSAGE_H
