//
// Created by raphael on 22/09/18.
//

#include "Exception.hpp"

Exception::Exception(const std::string &error) : _msg(error)
{
}

Exception::~Exception() throw()
{

}

const char  *Exception::what() const throw()
{
    return (_msg.c_str());
}
