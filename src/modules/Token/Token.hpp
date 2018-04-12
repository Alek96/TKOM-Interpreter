#ifndef INTERPRETER_TOKEN_HPP
#define INTERPRETER_TOKEN_HPP

#include <ostream>
#include "TokenType.hpp"
#include "TokenTypeDefiner.hpp"
#include "reader/SignPosition.hpp"

namespace tkom {
    struct Token {
        explicit Token(const TokenType& type = TokenType::Invalid);

        bool operator==(const Token &rhs) const;
        bool operator!=(const Token &rhs) const;

        bool operator<(const Token &rhs) const;
        bool operator>(const Token &rhs) const;
        bool operator<=(const Token &rhs) const;
        bool operator>=(const Token &rhs) const;

        friend std::ostream &operator<<(std::ostream &os, const Token &token);

        TokenType type;
        std::string value;
        SignPosition position;
    };

    inline std::ostream &operator<<(std::ostream &os, const Token &token) {
        os << "type: " << TokenTypeDefiner::getName(token.type)
           << ", value: " << token.value
           << ", position: " << token.position;
        return os;
    }
}


#endif //INTERPRETER_TOKEN_HPP
