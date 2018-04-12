#ifndef INTERPRETER_EXCEPTION_HPP
#define INTERPRETER_EXCEPTION_HPP

#include <iostream>
#include <stdexcept>
#include <sstream>

#include "token/Token.hpp"

namespace tkom {

    class Exception : public std::runtime_error {
        using std::runtime_error::runtime_error;
    };

    class InvalidTokenException : public Exception {
    public:
        explicit InvalidTokenException(Token &token) :
                Exception("Undefined token: " +
                          [&]() {
                              std::stringstream ss;
                              ss << token;
                              return ss.str();
                          }()) {}
    };
}

#endif //INTERPRETER_EXCEPTION_HPP
