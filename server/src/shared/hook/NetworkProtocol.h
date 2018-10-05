//
// Created by romain on 02/10/18.
//

#ifndef SERVER_NETWORKPROTOCOL_H
#define SERVER_NETWORKPROTOCOL_H


#include <unordered_map>
#include <memory>
#include "../../protocol/HelloConnectMessage.h"
#include "../../protocol/LoginMessage.h"
#include "../../protocol/LoginSuccessMessage.h"
#include "../../protocol/LoginFailedMessage.h"
#include "../../protocol/CallRequestMessage.h"
#include "../../protocol/ErrorResponseMessage.h"
#include "../../protocol/UpdateContactMessage.h"
#include "../../protocol/VoiceDataMessage.h"
#include "../../protocol/CallRefusedMessage.h"


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
                { HelloConnectMessage::OPCODE, packet_factory<HelloConnectMessage> },
                { LoginMessage::OPCODE, packet_factory<LoginMessage> },
                { LoginSuccessMessage::OPCODE, packet_factory<LoginSuccessMessage> },
                { LoginFailedMessage::OPCODE, packet_factory<LoginFailedMessage> },
                { CallRequestMessage::OPCODE, packet_factory<CallRequestMessage> },
                { ErrorResponseMessage::OPCODE, packet_factory<ErrorResponseMessage> },
                { UpdateContactMessage::OPCODE, packet_factory<UpdateContactMessage> },
                { VoiceDataMessage::OPCODE, packet_factory<VoiceDataMessage> },
                { CallRefusedMessage::OPCODE, packet_factory<CallRefusedMessage> }
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
