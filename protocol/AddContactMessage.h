//
// Created by romain on 04/10/18.
//

#ifndef SERVER_UPDATECONTACTMESSAGE_H
#define SERVER_UPDATECONTACTMESSAGE_H

#include "../shared/hook/NetworkMessage.h"
#include "../shared/Util.h"
#include <iostream>

struct AddContactMessage : NetworkMessage {
    static opcode constexpr OPCODE = 5;

    std::vector<std::string> newClients;

    AddContactMessage()
            : NetworkMessage(OPCODE),
                newClients()
    {}
    AddContactMessage(std::vector<std::string> const &newClients_)
            : NetworkMessage(OPCODE),
              newClients(newClients_)
    {
    }
    AddContactMessage(std::string const &newClient)
            : NetworkMessage(OPCODE),
              newClients()
    {
        newClients.push_back(newClient);
    }

    void serialize(BinaryWriter &writer) const override {
        writer & newClients;
    }

    void deserialize(BinaryReader &reader) override {
        reader & newClients;
    }

    std::ostream &dump(std::ostream &o) const override {
        return o << "AddContactMessage(newClients=" << util::dumpList(newClients) << ")";
    }
};

#endif //SERVER_UPDATECONTACTMESSAGE_H
