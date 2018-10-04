//
// Created by romain on 01/10/18.
//

#ifndef SERVER_HELLOCONNECTMESSAGE_H
#define SERVER_HELLOCONNECTMESSAGE_H

#include "../shared/BinaryWriter.h"
#include "../shared/BinaryReader.h"
#include "../shared/hook/NetworkMessage.h"

struct HelloConnectMessage : NetworkMessage {
    static opcode constexpr OPCODE = 1;

    HelloConnectMessage() : NetworkMessage(OPCODE) {}

    void serialize(BinaryWriter &writer) const override {
    }

    void deserialize(BinaryReader &reader) override {
    }

    std::ostream &dump(std::ostream &o) const override {
        return o << "HelloConnectMessage()";
    }
};

#endif //SERVER_HELLOCONNECTMESSAGE_H
