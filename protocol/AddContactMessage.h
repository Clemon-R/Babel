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
       for (auto &s: newClients)
           printf("got %s\n", &s[0]);
    }
    AddContactMessage(std::string const &newClient)
            : NetworkMessage(OPCODE),
              newClients()
    {
        newClients.push_back(newClient);
        printf("%s\n", newClients.at(0).c_str());
    }

    void serialize(BinaryWriter &writer) const override {
        for (auto &s : newClients)
            std::cout << "send " <<  s << std::endl;
        writer & newClients;
        for (auto &by: writer.bytes())
            printf("%d.", by);
        printf("\n");
        for (auto &s : newClients)
            std::cout << "send2 " <<  s << std::endl;
    }

    void deserialize(BinaryReader &reader) override {
        reader & newClients;
    }

    std::ostream &dump(std::ostream &o) const override {
        if (newClients.size() > 0)
            printf("%s\n", newClients.at(0).c_str());
        return o << "AddContactMessage(newClients=" << util::dumpList(newClients) << ")";
    }
};

#endif //SERVER_UPDATECONTACTMESSAGE_H
