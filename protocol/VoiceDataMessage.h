//
// Created by romain on 05/10/18.
//

#ifndef SERVER_VOICEDATAMESSAGE_H
#define SERVER_VOICEDATAMESSAGE_H

#include "../shared/hook/NetworkMessage.h"
#include "../shared/Util.h"

struct VoiceDataMessage : NetworkMessage {
    static opcode constexpr OPCODE = 7;

    std::vector<unsigned char> *data;
    ~VoiceDataMessage(){
        if (data){
            delete data;
            data = nullptr;
        }
    }

    VoiceDataMessage() : NetworkMessage(OPCODE) {}

    VoiceDataMessage(std::string const &data_) : NetworkMessage(OPCODE),
                                                 data(new std::vector<unsigned char>(&data_[0], &data_[0] + data_.size())) {}

    VoiceDataMessage(const boost::uint8_t *data_, sizet size)
            : NetworkMessage(OPCODE),
              data(new std::vector<unsigned char>(data_, data_ + size)) {}

    VoiceDataMessage(std::vector<unsigned char> const &data_)
            : NetworkMessage(OPCODE),
              data(new std::vector<unsigned char>(data_)) {}

    void serialize(BinaryWriter &writer) const override {
        writer & data;
    }

    void deserialize(BinaryReader &reader) override {
        reader & data;
    }

    std::ostream &dump(std::ostream &o) const override {
        return o << "VoiceDataMessage(data=[packed])";
    }
};


#endif //SERVER_VOICEDATAMESSAGE_H
