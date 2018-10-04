//
// Created by romain on 26/09/18.
//

#include "BinaryReader.h"

BinaryReader::BinaryReader()
        : _buffer(nullptr),
          _position(0)
{}

BinaryReader::BinaryReader(char const *buffer, sizet size)
        : _buffer(buffer),
          _position(0)
{}

std::string BinaryReader::readUtf() {
    boost::uint64_t size = readUlong();
    std::string value(_buffer + _position, size);
    _position += size;
    return value;
}

float BinaryReader::readFloat() {
    return readType<float>();
}

double BinaryReader::readDouble() {
    return readType<double>();
}

boost::int16_t BinaryReader::readShort() {
    return readType<boost::int16_t>();
}

boost::uint16_t BinaryReader::readUshort() {
    return readType<boost::uint16_t>();
}

boost::int32_t BinaryReader::readInt() {
    return readType<boost::int32_t>();
}

boost::uint32_t BinaryReader::readUint() {
    return readType<boost::uint32_t>();
}

boost::int64_t BinaryReader::readLong() {
    return readType<boost::int64_t>();
}

boost::uint64_t BinaryReader::readUlong() {
    return readType<boost::uint64_t>();
}

void BinaryReader::seek(sizet position) {
    _position = position;
}

void BinaryReader::reset(char const *buffer, sizet size) {
    _position = 0;
    _buffer = buffer;
    _size = size;
}

sizet BinaryReader::tell() const {
    return _position;
}
