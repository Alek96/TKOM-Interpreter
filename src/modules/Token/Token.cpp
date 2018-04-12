#include "Token.hpp"

#include "TokenTypeDefiner.hpp"

using namespace tkom;

Token::Token(const TokenType &type) :
        type(type),
        value(""),
        position() {}

bool Token::operator==(const Token &rhs) const {
    return type == rhs.type &&
           value == rhs.value &&
           position == rhs.position;
}

bool Token::operator!=(const Token &rhs) const {
    return !(rhs == *this);
}

bool Token::operator<(const Token &rhs) const {
    if (type < rhs.type)
        return true;
    if (rhs.type < type)
        return false;
    if (value < rhs.value)
        return true;
    if (rhs.value < value)
        return false;
    return position < rhs.position;
}

bool Token::operator>(const Token &rhs) const {
    return rhs < *this;
}

bool Token::operator<=(const Token &rhs) const {
    return !(rhs < *this);
}

bool Token::operator>=(const Token &rhs) const {
    return !(*this < rhs);
}
