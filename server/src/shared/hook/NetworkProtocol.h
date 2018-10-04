//
// Created by romain on 02/10/18.
//

#ifndef SERVER_NETWORKPROTOCOL_H
#define SERVER_NETWORKPROTOCOL_H


#include <unordered_map>
#include <memory>
#include "../../protocol/HelloConnectMessage.h"


namespace NetworkProtocol {
    template<typename T>
    std::unique_ptr<NetworkMessage> packet_factory() {
        return std::unique_ptr<NetworkMessage>(new T());
    }

    /** private **/
    namespace {
        /**
         * Define all protocol messages here,
         * {key=opcode, value=packetFactory<packetType>}
         */
        const std::unordered_map<opcode, std::unique_ptr<NetworkMessage>(*)()> messages {
                { HelloConnectMessage::OPCODE, packet_factory<HelloConnectMessage> }
        };
    }

    void serialize(NetworkMessage const &msg, BinaryWriter &writer) {
        writer & msg.getOpcode();
        msg.serialize(writer);
    }

    std::unique_ptr<NetworkMessage> deserialize(BinaryReader &reader) {
        opcode id;
        reader & id;

        try {
            std::unique_ptr<NetworkMessage> message(messages.at(id)());
            message->deserialize(reader);
            return message;
        } catch (std::exception &e) {
            throw std::runtime_error("invalid protocol id received");
        }
    }
}

#endif //SERVER_NETWORKPROTOCOL_H
