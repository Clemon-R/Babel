//
// Created by romain on 05/10/18.
//

#ifndef SERVER_VOICEDATAMESSAGE_H
#define SERVER_VOICEDATAMESSAGE_H

#include "../shared/hook/NetworkMessage.h"
#include "../shared/Util.h"

struct VoiceDataMessage : NetworkMessage {
    static opcode constexpr OPCODE = 8;

    std::vector<char> data;

    VoiceDataMessage() : NetworkMessage(OPCODE) {}
    VoiceDataMessage(std::string const &data_) : NetworkMessage(OPCODE),
                                           data(&data_[0], &data_[0] + data_.size())
    {}
    VoiceDataMessage(std::vector<char> const &data_)
            : NetworkMessage(OPCODE),
              data(data_)
    {}

    void serialize(BinaryWriter &writer) const override {
        writer & data;
    }

    void deserialize(BinaryReader &reader) override {
        reader & data;
    }

    std::ostream &dump(std::ostream &o) const override {
        return o << "VoiceDataMessage(data=" << util::dumpBinary(data) << ")";
    }
};


#endif //SERVER_VOICEDATAMESSAGE_H
