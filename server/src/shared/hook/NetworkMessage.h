//
// Created by romain on 02/10/18.
//

#ifndef SERVER_NETWORKMESSAGE_H
#define SERVER_NETWORKMESSAGE_H

#include "../BinaryWriter.h"
#include "../BinaryReader.h"

using opcode = boost::uint16_t;

struct NetworkMessage {
    virtual ~NetworkMessage() = default;

    explicit NetworkMessage(opcode id) : _id(id) {}

    virtual void serialize(BinaryWriter &writer) const = 0;
    virtual void deserialize(BinaryReader &reader) = 0;
    virtual std::ostream &dump(std::ostream &o) const = 0;

    opcode getOpcode() const {
        return _id;
    }

private:
    opcode _id;
};

inline std::ostream &operator<<(std::ostream &o, const NetworkMessage &msg) {
    return msg.dump(o);
}

#endif //SERVER_NETWORKMESSAGE_H
