//
// Created by romain on 26/09/18.
//

#include "BinaryWriter.h"

BinaryWriter::BinaryWriter()
        : _buffer(),
          _position(0)
{}

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

