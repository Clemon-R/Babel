//
// Created by romain on 26/09/18.
//

#ifndef SERVER_BINARYREADER_H
#define SERVER_BINARYREADER_H

#include "Network.h"

class BinaryReader {
public:
    BinaryReader();
    explicit BinaryReader(char const *buffer);

    void seek(sizet set);
    sizet tell() const;
    void reset(char const *buffer);

    std::string readUtf();
    float readFloat();
    double readDouble();
    boost::int16_t readShort();
    boost::uint16_t readUshort();
    boost::int32_t readInt();
    boost::uint32_t readUint();
    boost::int64_t readLong();
    boost::uint64_t readUlong();

private:
    template <class T>
    T readType();

private:
    char const *_buffer;
    sizet _position;
};


#endif //SERVER_BINARYREADER_H
