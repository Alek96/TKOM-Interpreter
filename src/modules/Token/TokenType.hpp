#ifndef INTERPRETER_TOKENTYPE_HPP
#define INTERPRETER_TOKENTYPE_HPP

#include <unordered_map>
#include <string>

namespace tkom{
    enum class TokenType : unsigned int {
        Function,
        If,
        While,
        Else,
        Return,
        Continue,
        Break,
        Var,
        Vec,
        Print,

        ParenthesisOpen,
        ParenthesisClose,
        BracketOpen,
        BracketClose,
        CurlyBracketOpen,
        CurlyBracketClose,
        Comma,
        Assignment,
        Semicolon,

        Negation,
        Or,
        And,
        Equality,
        Inequality,
        Less,
        Greater,
        LessOrEqual,
        GreaterOrEqual,
        Plus,
        Minus,
        Multiply,
        Divide,
        Modulo,

        Identifier,
        NumberLiteral,
        StringLiteral,

        Invalid,
        EndOfFile
    };
}

#endif //INTERPRETER_TOKENTYPE_HPP