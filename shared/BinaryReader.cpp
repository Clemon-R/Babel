//
// Created by romain on 26/09/18.
//

#include "BinaryReader.h"

BinaryReader::BinaryReader()
        : _buffer(nullptr),
          _position(0)
{}

BinaryReader::BinaryReader(const boost::uint8_t *buffer, sizet size)
        : _buffer(buffer),
          _position(0)
{}

void BinaryReader::seek(sizet position) {
    _position = position;
}

void BinaryReader::reset(const boost::uint8_t *buffer, sizet size) {
    _position = 0;
    _buffer = buffer;
    _size = size;
}

sizet BinaryReader::tell() const {
    return _position;
}
