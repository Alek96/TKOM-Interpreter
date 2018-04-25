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

        void readNextToken();
        const Token & getToken() const;

    private:
        Reader reader;
        Token token;

        void defineTokenKeywordOrIdentifier();
        void defineTokenNumberLiteral();
        void defineTokenWithSpecialCharacter();

        void defineTokenStringLiteral();
        void acceptSign(char sign, TokenType exist, TokenType notExist);
    };
}

#endif //INTERPRETER_LEXER_HPP
