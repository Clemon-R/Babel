//
// Created by romain on 04/10/18.
//

#ifndef SERVER_UTIL_H
#define SERVER_UTIL_H

#include <ostream>
#include <vector>
#include "Network.h"

namespace util {
    template<class T>
    inline std::string dumpList(std::vector<T> const &list) {
        sizet size = list.size();
        std::string result("{ ");
        for (sizet i=0; i < size; ++i) {
            result += std::to_string(list.at(i));
            if (i != size - 1)
                result += ", ";
        }
        result += " }";
        return result;
    }

    inline std::string dumpList(std::vector<std::string> const &list) {
        sizet size = list.size();
        std::string result("{ ");
        for (sizet i=0; i < size; ++i) {
            result += "\"" + list.at(i) + "\"";
            if (i != size - 1)
                result += ", ";
        }
        result += " }";
        return result;
    }

    inline std::string dumpBinary(std::string const &binary) {
        sizet size = binary.size();
        std::string data;

        for (sizet i=0; i < size; ++i) {
            data += std::to_string(binary[i]);
            if (i != size - 1)
                data += "|";
        }
        return data;
    }

    inline std::string dumpBinary(std::vector<char> const &binary) {
        sizet size = binary.size();
        std::string data;

        for (sizet i=0; i < size; ++i) {
            data += std::to_string(binary[i]);
            if (i != size - 1)
                data += "|";
        }
        return data;
    }
}

#endif //SERVER_UTIL_H
