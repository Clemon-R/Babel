//
// Created by raphael on 22/09/18.
//

#ifndef CLIENT_EXCEPTION_H
#define CLIENT_EXCEPTION_H

#include <exception>
#include <iostream>

class Exception : public std::exception{
public:
    Exception(const std::string &error);
    virtual ~Exception() throw();

    virtual const char  *what() const throw();
private:
    std::string _msg;
};


#endif //CLIENT_EXCEPTION_H
