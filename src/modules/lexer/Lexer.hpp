#ifndef INTERPRETER_LEXER_HPP
#define INTERPRETER_LEXER_HPP

#include <istream>
#include <memory>

#include "reader/Reader.hpp"
#include "Token/Token.hpp"

namespace tkom {

    class Lexer {
    public:
        explicit Lexer(std::istream& istream);

        Lexer(const Lexer&) = delete;
        Lexer& operator=(const Lexer&) = delete;

        void readNextToken();
        const Token getToken() const;

    private:
        Reader reader;
        Token token;
        char sign;

        void defineTokenKeywordOrIdentifier();
        void defineTokenNumberLiteral();
        void defineTokenWithSpecialCharacter();

        void defineTokenStringLiteral();
    };
}

#endif //INTERPRETER_LEXER_HPP
