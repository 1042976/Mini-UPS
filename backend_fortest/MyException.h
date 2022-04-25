//
// Created on 4/6/22.
//

#ifndef FINALPROJECT_MYEXCEPTION_H
#define FINALPROJECT_MYEXCEPTION_H

#include <exception>
#include <string>

using std::exception;
using std::string;

class MyException : public exception {
private:
    string message;

public:
    MyException() : message(std::string("Exception occurs!") + "\n") {}

    MyException(const string &_message) : message(_message + "\n") {}

    const char *what() const

    noexcept override{return message.c_str();}
};

#endif //FINALPROJECT_MYEXCEPTION_H
