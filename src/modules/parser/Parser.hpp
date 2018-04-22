#ifndef INTERPRETER_PARSER_HPP
#define INTERPRETER_PARSER_HPP

#include <memory>
#include <functional>
#include "lexer/Lexer.hpp"
#include "ast/Program.hpp"

#include "ast/statement/Statement.hpp"
#include "ast/expression/Expression.hpp"

namespace tkom {

    class Parser {
    public:
        explicit Parser(std::unique_ptr<Lexer> lexer);

        ~Parser() = default;

        void parse();
//        void run();

    private:
        std::unique_ptr<Lexer> lexer;
        ast::Program program;
        ast::BlockStatement* block = nullptr;

        void acceptOrThrow(TokenType type, std::function<void()> ifTrue = std::function<void()>());
        bool accept(TokenType type, std::function<void()> ifTrue = std::function<void()>());
        void throwExpectedTokens(std::list<TokenType> tokens);
        void programParse();

        void functionDefParse();

        void blockStatementParse(ast::BlockStatement &newBlock);
        void parametersParse(ast::FunctionDef &def);

        std::unique_ptr<ast::Statement> initStatementParse();
        std::unique_ptr<ast::Statement> assignStatementOrFunctionCallParse(Token& tokenId);
        std::unique_ptr<ast::Statement> assignStatementParse(ast::Variable& variable);
        std::unique_ptr<ast::Statement> functionCallParse(Token &tokenId);
        std::unique_ptr<ast::Statement> ifStatementParse();
        std::unique_ptr<ast::Statement> whileStatementParse();
        std::unique_ptr<ast::Statement> returnStatementParse();
        std::unique_ptr<ast::Statement> printStatementParse();

        std::unique_ptr<ast::Expression> logicExprParse();
        std::unique_ptr<ast::Expression> andExprParser();
        std::unique_ptr<ast::Expression> relationalExprParser();
        std::unique_ptr<ast::Expression> baseLogicParser();
        std::unique_ptr<ast::Expression> mathExprParser();
        std::unique_ptr<ast::Expression> multiplicativeExprParser();
        std::unique_ptr<ast::Expression> baseMathExprParser();

        ast::Variable vectorLiteralParse();
        const bool existVariable(Token &tokenId);
    };
}

#endif //INTERPRETER_PARSER_HPP
