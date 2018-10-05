//
// Created by romain on 05/10/18.
//

#ifndef BABEL_DELCONTACTMESSAGE_H
#define BABEL_DELCONTACTMESSAGE_H

#include "../shared/hook/NetworkMessage.h"
#include "../shared/Util.h"

struct DelContactMessage : NetworkMessage {
    static opcode constexpr OPCODE = 10;

    std::vector<std::string> delClients;

    DelContactMessage() : NetworkMessage(OPCODE) {}
    DelContactMessage(std::vector<std::string> const &delClients_)
            : NetworkMessage(OPCODE),
              delClients(delClients_)
    {}
    DelContactMessage(std::string const &delClient)
            : NetworkMessage(OPCODE),
              delClients()
    {
        delClients.push_back(delClient);
    }

    void serialize(BinaryWriter &writer) const override {
        writer & delClients;
    }

    void deserialize(BinaryReader &reader) override {
        reader & delClients;
    }

    std::ostream &dump(std::ostream &o) const override {
        return o << "DelContactMessage(delClients=" << util::dumpList(delClients) << ")";
    }
};

#endif //BABEL_DELCONTACTMESSAGE_H
