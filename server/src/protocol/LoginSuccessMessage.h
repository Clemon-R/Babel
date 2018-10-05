//
// Created by romain on 04/10/18.
//

#ifndef SERVER_LOGINSUCCESSMESSAGE_H
#define SERVER_LOGINSUCCESSMESSAGE_H

#include "../shared/hook/NetworkMessage.h"

struct LoginSuccessMessage : NetworkMessage {
    static opcode constexpr OPCODE = 3;

    LoginSuccessMessage() : NetworkMessage(OPCODE) {}

    void serialize(BinaryWriter &writer) const override {
    }

    void deserialize(BinaryReader &reader) override {
    }

    std::ostream &dump(std::ostream &o) const override {
        return o << "LoginSuccessMessage()";
    }
};

#endif //SERVER_LOGINSUCCESSMESSAGE_H
