//
// Created by romain on 04/10/18.
//

#ifndef SERVER_UPDATECONTACTMESSAGE_H
#define SERVER_UPDATECONTACTMESSAGE_H

#include "../shared/hook/NetworkMessage.h"
#include "../shared/Util.h"

struct UpdateContactMessage : NetworkMessage {
    static opcode constexpr OPCODE = 5;

    std::vector<std::string> newClients;
    std::vector<std::string> disconnectedClients;

    UpdateContactMessage() : NetworkMessage(OPCODE) {}
    UpdateContactMessage(std::vector<std::string> const &newClients_, std::vector<std::string> const &dcClients_)
            : NetworkMessage(OPCODE),
              newClients(newClients_),
              disconnectedClients(dcClients_)
    {}

    void serialize(BinaryWriter &writer) const override {
        writer & newClients & disconnectedClients;
    }

    void deserialize(BinaryReader &reader) override {
        reader & newClients & disconnectedClients;
    }

    std::ostream &dump(std::ostream &o) const override {
        return o << "UpdateContactMessage(newClients=" << util::dumpList(newClients) << ", " <<
                "disconnectedClients=" << util::dumpList(disconnectedClients) << ")";
    }
};

#endif //SERVER_UPDATECONTACTMESSAGE_H
