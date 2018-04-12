#include "Lexer.hpp"
#include <cctype>
#include <iostream>

#include "Token/TokenTypeDefiner.hpp"
#include "exception/Exception.hpp"

using namespace tkom;

Lexer::Lexer(std::istream &istream)
        : reader(istream) {}

void Lexer::readNextToken() {
    sign = reader.get();
    while (std::isspace(sign) && !reader.eof())
        sign = reader.get();

    token = Token();
    token.position = reader.getPosition();

    if (reader.eof()) {
        token.type = TokenType::EndOfFile;
        return;
    }

    if (std::isalpha(sign)) {
        defineTokenKeywordOrIdentifier();
    } else if (std::isdigit(sign)) {
        defineTokenNumberLiteral();
    } else if (sign == '"') {
        defineTokenStringLiteral();
    } else {
        defineTokenWithSpecialCharacter();
    }

    ///throw invalid token exception
    if (token.type == TokenType::Invalid)
        throw InvalidTokenException(token);
}

const Token Lexer::getToken() const {
    return token;
}

void Lexer::defineTokenKeywordOrIdentifier() {
    std::string buffer;
    buffer.push_back(sign);

    while (std::isalnum(reader.peek()) || reader.peek() == '_' || reader.peek() == '$') {
        buffer.push_back(reader.get());
    }

    token.type = TokenTypeDefiner::find(buffer);
    if (token.type == TokenType::Invalid) {
        token.type = TokenType::Identifier;
        token.value = buffer;
    }
}

void Lexer::defineTokenNumberLiteral() {
    std::string buffer;
    buffer.push_back(sign);

    while (std::isdigit(reader.peek())) {
        buffer.push_back(reader.get());
    }

    token.type = TokenType::NumberLiteral;
    token.value = buffer;
}

void Lexer::defineTokenStringLiteral() {
    std::string buffer;

    while ((std::isprint(reader.peek()) || std::isspace(reader.peek()))
           && reader.peek() != '"'
           && !reader.eof()) {
        if (reader.peek() == '\\') {
            reader.get();
            if (reader.peek() == '"') {
                buffer.push_back(reader.get());
            } else {
                buffer.push_back('\\');
            }
        } else {
            buffer.push_back(reader.get());
        }
    }

    if (reader.peek() == '"') {
        reader.get();
        token.type = TokenType::StringLiteral;
    } else {
        token.type = TokenType::Invalid;
    }
    token.value = buffer;
}

void Lexer::defineTokenWithSpecialCharacter() {
    switch (sign) {
        case '=': {
            if (reader.peek() == '=') {
                reader.get();
                token.type = TokenType::Equality;
            } else {
                token.type = TokenType::Assignment;
            }
            break;
        }
        case '<': {
            if (reader.peek() == '=') {
                reader.get();
                token.type = TokenType::LessOrEqual;
            } else {
                token.type = TokenType::Less;
            }
            break;
        }
        case '>': {
            if (reader.peek() == '=') {
                reader.get();
                token.type = TokenType::GreaterOrEqual;
            } else {
                token.type = TokenType::Greater;
            }
            break;
        }
        case '!': {
            if (reader.peek() == '=') {
                reader.get();
                token.type = TokenType::Inequality;
            } else {
                token.type = TokenType::Negation;
            }
            break;
        }
        case '&': {
            if (reader.peek() == '&') {
                reader.get();
                token.type = TokenType::And;
            } else {
                token.type = TokenType::Invalid;
                token.value = sign;
            }
            break;
        }
        case '|': {
            if (reader.peek() == '|') {
                reader.get();
                token.type = TokenType::Or;
            } else {
                token.type = TokenType::Invalid;
                token.value = sign;
            }
            break;
        }
        default: {
            token.type = TokenTypeDefiner::find(sign);
            if(token.type == TokenType::Invalid)
                token.value = sign;
            break;
        }
    }
}
