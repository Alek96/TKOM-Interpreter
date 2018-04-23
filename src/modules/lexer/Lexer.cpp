#include "Lexer.hpp"
#include <cctype>
#include <iostream>
#include <functional>

#include "Token/TokenTypeDefiner.hpp"
#include "exception/Exception.hpp"

using namespace tkom;

Lexer::Lexer(std::istream &istream)
        : reader(istream) {}

void Lexer::readNextToken() {
    while (std::isspace(reader.peek()) && !reader.eof())
        reader.get();

    token = Token();
    token.position = reader.getPosition();

    if (reader.eof()) {
        token.type = TokenType::EndOfFile;
        return;
    }

    if (std::isalpha(reader.peek())) {
        defineTokenKeywordOrIdentifier();
    } else if (std::isdigit(reader.peek())) {
        defineTokenNumberLiteral();
    } else if (reader.peek() == '"') {
        defineTokenStringLiteral();
    } else {
        defineTokenWithSpecialCharacter();
    }

    ///throw invalid token exception
    if (token.type == TokenType::Invalid)
        throw InvalidTokenException(token);
}

const Token &Lexer::getToken() const {
    return token;
}

void Lexer::defineTokenKeywordOrIdentifier() {
    std::string buffer;
    buffer.push_back(reader.get());

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
    buffer.push_back(reader.get());

    while (std::isdigit(reader.peek())) {
        buffer.push_back(reader.get());
    }

    token.type = TokenType::NumberLiteral;
    token.value = buffer;
}

void Lexer::defineTokenStringLiteral() {
    reader.get();
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
    //dlaczego static sie j****
    std::unordered_map<char, std::function<void()>> signs = {
            {'=', [&]() { acceptSign('=', TokenType::Equality, TokenType::Assignment); }},
            {'<', [&]() { acceptSign('=', TokenType::LessOrEqual, TokenType::Less); }},
            {'>', [&]() { acceptSign('=', TokenType::GreaterOrEqual, TokenType::Greater); }},
            {'!', [&]() { acceptSign('=', TokenType::Inequality, TokenType::Negation); }},
            {'&', [&]() { acceptSign('&', TokenType::And, TokenType::Invalid); }},
            {'|', [&]() { acceptSign('|', TokenType::Or, TokenType::Invalid); }}
    };

    token.value.push_back(reader.peek());

    if (signs.count(reader.peek())) {
        signs.at(reader.peek())();
    } else {
        token.type = TokenTypeDefiner::find(reader.peek());
        if (token.type == TokenType::Invalid)
            token.value = reader.peek();
        reader.get();
    }
}

void Lexer::acceptSign(const char sign, const TokenType exist, const TokenType notExist) {
    reader.get();
    if (!reader.eof() && reader.peek() == sign) {
        reader.get();
        token.type = exist;
    } else {
        token.type = notExist;
    }
}


