//
// Created by romain on 26/09/18.
//

#ifndef SERVER_BINARYREADER_H
#define SERVER_BINARYREADER_H

#include "Network.h"

class BinaryReader {
public:
    BinaryReader();
    explicit BinaryReader(const boost::uint8_t *buffer, sizet size);

    void seek(sizet set);
    sizet tell() const;
    void reset(const boost::uint8_t *buffer, sizet size);

    template<class T>
    BinaryReader &operator&(T &primitive) {
        readType<T>(primitive);
        return *this;
    }

private:
    template<class T>
    void readType(T &value) {
        auto *casted = (char *) &value;
        sizet size = sizeof(T);

        if (_position + size > _size)
            throw std::runtime_error("exceeded buffer");

        for (sizet i=0; i < size; ++i)
            casted[i] = _buffer[_position + i];
        _position += size;
    }

    template<class T>
    void readType(std::string &value) {
        boost::uint64_t size;
        readType(size);

        if (_position + size > _size)
            throw std::runtime_error("exceeded buffer");

        value = std::string((char *) _buffer + _position, size);
        _position += size;
    }

    template<class T>
    void readType(std::vector<T> &list) {
        boost::uint64_t size;
        readType(size);
        sizet length = sizeof(T);

        if (_position + (size * length) > _size)
            throw std::runtime_error("exceeded buffer");

        for (boost::uint64_t j=0; j < size; ++j) {
            T value;
            readType(value);
            auto *casted = (char *) &value;

            for (sizet i=0; i < length; ++i)
                casted[i] = _buffer[_position + i];

            list.push_back(value);
            _position += length;
        }
    }

    template<class T>
    void readType(std::vector<boost::uint8_t> &list) {
        boost::uint64_t size;
        readType(size);

        if (_position + size > _size)
            throw std::runtime_error("exceeded buffer");

        list.insert(list.begin(), _buffer + _position, _buffer + size);
    }

    template<class T>
    void readType(std::vector<std::string> &list) {
        boost::uint64_t size;
        readType(size);

        for (boost::uint64_t j=0; j < size; ++j) {
            boost::uint64_t length;
            readType(length);

            if (_position + length > _size)
                throw std::runtime_error("exceeded buffer");

            list.emplace_back((char *)_buffer + _position, length);
            _position += length;
        }
    }

private:
    const boost::uint8_t *_buffer;
    sizet _size;
    sizet _position;
};


#endif //SERVER_BINARYREADER_H
