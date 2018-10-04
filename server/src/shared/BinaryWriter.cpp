//
// Created by romain on 26/09/18.
//

#include "BinaryWriter.h"

BinaryWriter::BinaryWriter()
        : _buffer(),
          _position(0)
{}

void BinaryWriter::writeUtf(std::string const &value) {
    boost::uint64_t size = value.size();
    writeUlong(size);
    _buffer.insert(_buffer.begin() + _position, value.c_str(), value.c_str() + size);
    _position += size;
}

void BinaryWriter::writeFloat(float value) {
    writeType(value);
}

void BinaryWriter::writeDouble(double value) {
    writeType(value);
}

void BinaryWriter::writeShort(boost::int16_t value) {
    writeType(value);
}

void BinaryWriter::writeUshort(boost::uint16_t value) {
    writeType(value);
}

void BinaryWriter::writeInt(boost::int32_t value) {
    writeType(value);
}

void BinaryWriter::writeUint(boost::uint32_t value) {
    writeType(value);
}

void BinaryWriter::writeLong(boost::int64_t value) {
    writeType(value);
}

void BinaryWriter::writeUlong(boost::uint64_t value) {
    writeType(value);
}

void BinaryWriter::seek(sizet set) {
    _position = set;
}

sizet BinaryWriter::tell() const {
    return _position;
}

buffer_t &BinaryWriter::bytes() {
    return _buffer;
}

void BinaryWriter::reset() {
    _position = 0;
    _buffer.clear();
}

