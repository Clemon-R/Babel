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
        writer & _4bytesIntTest & _8bytesUintTest & _stringTest;
    }

    void deserialize(BinaryReader &reader) override {
        reader & _4bytesIntTest & _8bytesUintTest & _stringTest;
    }

    std::ostream &dump(std::ostream &o) const override {
        return o << "HelloConnectMessage(" <<
                 "4bytesIntTest=" << _4bytesIntTest << ", " <<
                 "etc...)";
    }

    boost::int32_t _4bytesIntTest;
    boost::uint64_t _8bytesUintTest;
    std::string _stringTest;
};

#endif //SERVER_HELLOCONNECTMESSAGE_H
