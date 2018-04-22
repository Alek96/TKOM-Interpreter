#ifndef INTERPRETER_EXCEPTION_HPP
#define INTERPRETER_EXCEPTION_HPP

#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>

#include "token/Token.hpp"

namespace tkom {

    class Exception : public std::runtime_error {
        using std::runtime_error::runtime_error;
    };

    class InvalidTokenException : public Exception {
    public:
        explicit InvalidTokenException(const Token &token) :
                Exception("Undefined token: " +
                          [&]() {
                              std::stringstream ss;
                              ss << token;
                              return ss.str();
                          }()) {}
    };

    class MathException : public Exception {
    public:
        explicit MathException(const std::string message) :
                Exception(message) {}
    };

    class BadToken : public Exception {
    public:
        explicit BadToken(const std::string message) :
                Exception(message) {}
    };
}

#endif //INTERPRETER_EXCEPTION_HPP

///to string