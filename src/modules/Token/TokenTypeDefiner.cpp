#include "TokenTypeDefiner.hpp"

using namespace tkom;

const bool TokenTypeDefiner::exist(const std::string &name) {
    return getKeywords().count(name);
}

const bool TokenTypeDefiner::exist(const char sign) {
    return getSimpleSigns().count(sign);
}

const TokenType TokenTypeDefiner::find(const std::string &name) {
    auto type = getKeywords().find(name);
    return type == getKeywords().end() ? TokenType::Invalid : type->second;
}

const TokenType TokenTypeDefiner::find(char sign) {
    auto type = getSimpleSigns().find(sign);
    return type == getSimpleSigns().end() ? TokenType::Invalid : type->second;
}

const std::string TokenTypeDefiner::getName(const TokenType &type) {
    static const std::unordered_map<TokenType, std::string> typeNames = {
            {TokenType::Function,          "Function"},
            {TokenType::If,                "If"},
            {TokenType::While,             "While"},
            {TokenType::Else,              "Else"},
            {TokenType::Return,            "Return"},
            {TokenType::Continue,          "Continue"},
            {TokenType::Break,             "Break"},
            {TokenType::Var,               "Var"},
            {TokenType::Vec,               "Vec"},
            {TokenType::Print,             "Print"},

            {TokenType::ParenthesisOpen,   "ParenthesisOpen"},
            {TokenType::ParenthesisClose,  "ParenthesisClose"},
            {TokenType::BracketOpen,       "BracketOpen"},
            {TokenType::BracketClose,      "BracketClose"},
            {TokenType::CurlyBracketOpen,  "CurlyBracketOpen"},
            {TokenType::CurlyBracketClose, "CurlyBracketClose"},
            {TokenType::Comma,             "Comma"},
            {TokenType::Assignment,        "Assignment"},
            {TokenType::Semicolon,         "Semicolon"},

            {TokenType::Negation,          "Negation"},
            {TokenType::Or,                "Or"},
            {TokenType::And,               "And"},
            {TokenType::Equality,          "Equality"},
            {TokenType::Inequality,        "Inequality"},
            {TokenType::Less,              "Less"},
            {TokenType::Greater,           "Greater"},
            {TokenType::LessOrEqual,       "LessOrEqual"},
            {TokenType::GreaterOrEqual,    "GreaterOrEqual"},
            {TokenType::Plus,              "Plus"},
            {TokenType::Minus,             "Minus"},
            {TokenType::Multiply,          "Multiply"},
            {TokenType::Divide,            "Divide"},
            {TokenType::Modulo,            "Modulo"},

            {TokenType::Identifier,        "Identifier"},
            {TokenType::NumberLiteral,     "NumberLiteral"},
            {TokenType::StringLiteral,     "StringLiteral"},

            {TokenType::Invalid,           "Invalid"},
            {TokenType::EndOfFile,         "EndOfFile"}
    };

    return typeNames.at(type);
}

const std::unordered_map<std::string, TokenType> &TokenTypeDefiner::getKeywords() {
    static const std::unordered_map<std::string, TokenType> &keywords = {
            {"function", TokenType::Function},
            {"if",       TokenType::If},
            {"while",    TokenType::While},
            {"else",     TokenType::Else},
            {"return",   TokenType::Return},
            {"continue", TokenType::Continue},
            {"break",    TokenType::Break},
            {"var",      TokenType::Var},
            {"vec",      TokenType::Vec},
            {"print",    TokenType::Print}
    };

    return keywords;
}

const std::unordered_map<char, TokenType> &TokenTypeDefiner::getSimpleSigns() {
    static const std::unordered_map<char, TokenType> &simpleSigns = {
            {'(', TokenType::ParenthesisOpen},
            {')', TokenType::ParenthesisClose},
            {'[', TokenType::BracketOpen},
            {']', TokenType::BracketClose},
            {'{', TokenType::CurlyBracketOpen},
            {'}', TokenType::CurlyBracketClose},
            {',', TokenType::Comma},
            {'=', TokenType::Assignment},
            {';', TokenType::Semicolon},

            {'!', TokenType::Negation},
            {'+', TokenType::Plus},
            {'-', TokenType::Minus},
            {'*', TokenType::Multiply},
            {'/', TokenType::Divide},
            {'%', TokenType::Modulo}
    };

    return simpleSigns;
}

