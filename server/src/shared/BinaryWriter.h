//
// Created by romain on 26/09/18.
//

#ifndef SERVER_BINARYWRITER_H
#define SERVER_BINARYWRITER_H

#include "Network.h"

using buffer_t = std::vector<char>;

class BinaryWriter {
public:
    BinaryWriter();

    buffer_t &bytes();
    void seek(sizet set);
    sizet tell() const;
    void reset();

    template<class T>
    BinaryWriter &operator&(T primitive) {
        writeType<T>(primitive);
        return *this;
    }

private:
    template<class T>
    void writeType(T value) {
        sizet size = sizeof(T);
        _buffer.insert(_buffer.begin() + _position, (char *)&value, (char *)&value + size);
        _position += size;
    }

    template<class T>
    void writeType(std::vector<T> list) {
        sizet size = sizeof(T);

        writeType((boost::uint64_t) list.size());
        for (sizet i=0; i < list.size(); ++i) {
            auto value = (char *) &list[i];
            _buffer.insert(_buffer.begin() + _position, &value, &value + size);
            _position += size;
        }
    }

    template<class T>
    void writeType(std::vector<std::string> list) {
        writeType((boost::uint64_t) list.size());
        for (sizet i=0; i < list.size(); ++i) {
            writeType((boost::uint64_t) list[i].size());
            _buffer.insert(_buffer.begin() + _position, &list.at(i)[0], &list.at(i)[0] + list.at(i).size());
            _position += list.at(i).size();
        }
    }

    template<class T>
    void writeType(std::string const &value) {
        boost::uint64_t size = value.size();

        writeType(size);
        _buffer.insert(_buffer.begin() + _position, value.c_str(), value.c_str() + size);
        _position += size;
    }

private:
    buffer_t _buffer;
    sizet _position;
};


#endif //SERVER_BINARYWRITER_H
