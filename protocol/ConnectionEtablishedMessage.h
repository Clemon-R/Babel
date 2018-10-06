//
// Created by root on 06/10/18.
//

#ifndef BABEL_CONNECTIONETABLISHEDMESSAGE_H
#define BABEL_CONNECTIONETABLISHEDMESSAGE_H

#include "../shared/BinaryWriter.h"
#include "../shared/BinaryReader.h"
#include "../shared/hook/NetworkMessage.h"

struct ConnectionEtablishedMessage : NetworkMessage {
    static opcode constexpr OPCODE = 11;

    ConnectionEtablishedMessage() : NetworkMessage(OPCODE) {}

    void serialize(BinaryWriter &writer) const override {
    }

    void deserialize(BinaryReader &reader) override {
    }

    std::ostream &dump(std::ostream &o) const override {
        return o << "ConnectionEtablishedMessage()";
    }
};

#endif //BABEL_CONNECTIONETABLISHEDMESSAGE_H
