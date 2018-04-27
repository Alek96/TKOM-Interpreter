#include "Parser.hpp"

#include <list>
#include <sstream>
#include <functional>
#include "exception/Exception.hpp"

#include "ast/statement/ReturnStatement.hpp"
#include "ast/statement/AssignStatement.hpp"
#include "ast/statement/IfStatement.hpp"
#include "ast/statement/WhileStatement.hpp"
#include "ast/statement/FunctionCall.hpp"
#include "ast/statement/PrintStatement.hpp"

#include "ast/expression/LogicExpr.hpp"

#include <iostream>

using namespace tkom;
using namespace tkom::ast;

Parser::Parser(std::unique_ptr<Lexer> lexer_)
        : lexer(std::move(lexer_)) {
}

void Parser::setLexer(std::unique_ptr<Lexer> lexer) {
    Parser::lexer = std::move(lexer);
}

void Parser::clearLexer() {
    lexer.reset(nullptr);
}

void Parser::parse() {
    if(lexer) {
        lexer->readNextToken();
        programParse();
    }
}

ast::Return Parser::run() {
    return program.run();
}

bool Parser::accept(const TokenType type, const std::function<void()> ifTrue) {
    if (lexer->getToken().type == type) {
        if (ifTrue)
            ifTrue();
        lexer->readNextToken();
        return true;
    } else {
        return false;
    }
}

void Parser::acceptOrThrow(const TokenType type, const std::function<void()> ifTrue) {
    if (!accept(type, ifTrue)) {
        throwExpectedTokens({type});
    }
}

void Parser::throwExpectedTokens(std::list<TokenType> tokens) {
    std::stringstream ss;
    ss << "Expected Tokens: ";
    for (auto &&token : tokens) {
        ss << TokenTypeDefiner::getName(token) << ", ";
    }
    ss << "at line: " << lexer->getToken().position;
    throw BadToken(ss.str());
}


void Parser::programParse() {
    while (lexer->getToken().type != TokenType::EndOfFile) {
        if (accept(TokenType::Function)) {
            functionDefParse();
        } else {
            throwExpectedTokens({TokenType::EndOfFile,
                                 TokenType::Function});
        }
    }
}

void Parser::functionDefParse() {
    std::unique_ptr<FunctionDef> function;

    acceptOrThrow(TokenType::Identifier, [&]() {
        function = std::make_unique<FunctionDef>(lexer->getToken().value);
    });

    acceptOrThrow(TokenType::ParenthesisOpen);
    parametersParse(*function);

    FunctionDef* func = function.get();
    program.addFunction(std::move(function));

    acceptOrThrow(TokenType::CurlyBracketOpen);
    blockStatementParse(func->getFunctionBlock());
}

void Parser::parametersParse(ast::FunctionDef &function) {

    if (accept(TokenType::Identifier, [&]() { function.addParameter(lexer->getToken().value); })) {

        while (accept(TokenType::Comma)) {
            acceptOrThrow(TokenType::Identifier, [&]() {
                function.addParameter(lexer->getToken().value);
            });
        }
    }
    acceptOrThrow(TokenType::ParenthesisClose);
}

void Parser::blockStatementParse(ast::BlockStatement &newBlock) {
    block = &newBlock;
    Token token;

    std::unordered_map<TokenType, std::function<void()>> statement = {
            {TokenType::Var,              [&]() {
                block->addInstruction(std::move(initStatementParse()));
            }},
            {TokenType::Identifier,       [&]() {
                block->addInstruction(std::move(assignStatementOrFunctionCallParse(token)));
            }},
            {TokenType::If,               [&]() {
                block->addInstruction(std::move(ifStatementParse()));
            }},
            {TokenType::While,            [&]() {
                block->addInstruction(std::move(whileStatementParse()));
            }},
            {TokenType::Return,           [&]() {
                block->addInstruction(std::move(returnStatementParse()));
            }},
            {TokenType::Continue,         [&]() {
                block->addInstruction(std::make_unique<ReturnStatement>(Return::_continue));
                acceptOrThrow(TokenType::Semicolon);
            }},
            {TokenType::Break,            [&]() {
                block->addInstruction(std::make_unique<ReturnStatement>(Return::_break));
                acceptOrThrow(TokenType::Semicolon);
            }},
            {TokenType::Print,            [&]() {
                block->addInstruction(std::move(printStatementParse()));
            }},
            {TokenType::CurlyBracketOpen, [&]() {
                auto newNewBlock = std::make_unique<BlockStatement>(block);
                blockStatementParse(*newNewBlock);
                block->addInstruction(std::move(newNewBlock));
            }}
    };

    while (!accept(TokenType::CurlyBracketClose)) {
        token = lexer->getToken();
        lexer->readNextToken();

        if (statement.count(token.type)) {
            statement.at(token.type)();
        } else {
            throwExpectedTokens({TokenType::If,
                                 TokenType::While,
                                 TokenType::Return,
                                 TokenType::Var,
                                 TokenType::Identifier,
                                 TokenType::Continue,
                                 TokenType::Break,
                                 TokenType::Print,
                                 TokenType::CurlyBracketOpen});
        }
    }

    block = const_cast<BlockStatement *>(newBlock.getParentBlock());
}

std::unique_ptr<ast::Statement> Parser::initStatementParse() {
    Token tokenId;

    acceptOrThrow(TokenType::Identifier, [&]() {
        tokenId = lexer->getToken();
    });

    if (block->existVariable(tokenId.value)) {
        throw Exception(
                "Variable already exist: " + tokenId.value +
                " at line: " + tokenId.position.toString());
    }

    block->addVariable(tokenId.value, Variable());
    std::unique_ptr<Expression> expr = std::make_unique<BaseMathExpr>(new Variable());

    if (accept(TokenType::Assignment)) {
        expr = std::move(logicExprParse());
    }

    acceptOrThrow(TokenType::Semicolon);

    return std::make_unique<AssignStatement>(block->findVariable(tokenId.value, tokenId), std::move(expr));
}

std::unique_ptr<ast::Statement> Parser::assignStatementOrFunctionCallParse(Token &tokenId) {
    std::unique_ptr<ast::Statement> statement;

    if (accept(TokenType::ParenthesisOpen)) {
        //function
        statement = std::move(functionCallParse(tokenId));
        acceptOrThrow(TokenType::Semicolon);
    } else {
        //variable
        existVariable(tokenId);
        statement = std::move(assignStatementParse(block->findVariable(tokenId.value, tokenId)));
    }
    return std::move(statement);
}

std::unique_ptr<ast::Statement> Parser::assignStatementParse(Variable &variable) {
    std::unique_ptr<AssignStatement> assignStatement;

    std::function<std::unique_ptr<Expression>()> AssignmentLogicExpr = [&]() {
        acceptOrThrow(TokenType::Assignment);
        std::unique_ptr<Expression> logicExpr(logicExprParse());
        acceptOrThrow(TokenType::Semicolon);
        return std::move(logicExpr);
    };

    if (accept(TokenType::BracketOpen)) {
        //variable + index
        Token token;
        acceptOrThrow(TokenType::NumberLiteral, [&]() { token = lexer->getToken(); });
        acceptOrThrow(TokenType::BracketClose);

        assignStatement = std::make_unique<AssignStatement>(variable,
                                                            static_cast<unsigned int>(std::stoi(token.value)),
                                                            std::move(AssignmentLogicExpr()));
        assignStatement->setPosition(token.position);
    } else {
        //variable
        assignStatement = std::make_unique<AssignStatement>(variable, std::move(AssignmentLogicExpr()));
    }

    return std::move(assignStatement);
}

std::unique_ptr<ast::Statement> Parser::functionCallParse(Token &tokenId) {
    if (!program.existFunction(tokenId.value)) {
        throw Exception(
                "Function not found: " + tokenId.value +
                " at line: " + tokenId.position.toString());
    }

    FunctionDef &functionDef = program.findFunction(tokenId.value);
    auto functionCall = std::make_unique<FunctionCall>(functionDef);

    if (!accept(TokenType::ParenthesisClose)) {
        functionCall->addExpression(logicExprParse());
        while (!accept(TokenType::ParenthesisClose)) {
            acceptOrThrow(TokenType::Comma);
            functionCall->addExpression(logicExprParse());
        }
    }

    if (functionDef.size() != functionCall->size()) {
        throw Exception(
                "Wrong number of parameters in functionCall: "
                " at line: " + tokenId.position.toString());
    }

    return std::move(functionCall);
}

std::unique_ptr<ast::Statement> Parser::ifStatementParse() {
    std::unique_ptr<Expression> expression;
    std::unique_ptr<BlockStatement> ifBlock;
    std::unique_ptr<BlockStatement> elseBlock;

    acceptOrThrow(TokenType::ParenthesisOpen);
    expression = std::move(logicExprParse());
    acceptOrThrow(TokenType::ParenthesisClose);

    acceptOrThrow(TokenType::CurlyBracketOpen);
    ifBlock = std::make_unique<BlockStatement>(block);
    blockStatementParse(*ifBlock);

    if (accept(TokenType::Else)) {
        acceptOrThrow(TokenType::CurlyBracketOpen);
        elseBlock = std::make_unique<BlockStatement>(block);
        blockStatementParse(*elseBlock);
    }

    return std::make_unique<IfStatement>(std::move(expression),
                                         std::move(ifBlock),
                                         std::move(elseBlock));
}

std::unique_ptr<ast::Statement> Parser::whileStatementParse() {
    std::unique_ptr<WhileStatement> whileStatement;
    std::unique_ptr<Expression> expression;
    std::unique_ptr<BlockStatement> whileBlock;
    Token token;

    acceptOrThrow(TokenType::ParenthesisOpen, [&]() { token = lexer->getToken(); });
    expression = std::move(logicExprParse());
    acceptOrThrow(TokenType::ParenthesisClose);

    acceptOrThrow(TokenType::CurlyBracketOpen);
    whileBlock = std::make_unique<BlockStatement>(block);
    blockStatementParse(*whileBlock);

    whileStatement = std::make_unique<WhileStatement>(std::move(expression),
                                                      std::move(whileBlock));
    whileStatement->setPosition(token.position);
    return std::move(whileStatement);
}

std::unique_ptr<ast::Statement> Parser::returnStatementParse() {
    auto returnStatement = std::make_unique<ReturnStatement>(std::move(logicExprParse()));
    acceptOrThrow(TokenType::Semicolon);
    return std::move(returnStatement);
}

std::unique_ptr<ast::Statement> Parser::printStatementParse() {
    std::unique_ptr<PrintStatement> printStatement = std::make_unique<PrintStatement>();

    auto add = [&]() {
        if (accept(TokenType::StringLiteral, [&]() {
            printStatement->addString(lexer->getToken().value);
        })) {
        } else {
            printStatement->addExpression(std::move(logicExprParse()));
        }
    };

    acceptOrThrow(TokenType::ParenthesisOpen);
    add();
    while (accept(TokenType::Comma)) {
        add();
    }
    acceptOrThrow(TokenType::ParenthesisClose);
    acceptOrThrow(TokenType::Semicolon);

    return std::move(printStatement);
}


std::unique_ptr<ast::Expression> Parser::logicExprParse() {
    std::unique_ptr<LogicExpr> logicExpr = std::make_unique<LogicExpr>(std::move(andExprParser()));

    while (accept(TokenType::Or)) {
        logicExpr->addOr(std::move(andExprParser()));
    }

    return std::move(logicExpr);
}

std::unique_ptr<ast::Expression> Parser::andExprParser() {
    std::unique_ptr<AndExpr> andExpr = std::make_unique<AndExpr>(std::move(relationalExprParser()));

    while (accept(TokenType::And)) {
        andExpr->addAnd(std::move(relationalExprParser()));
    }

    return std::move(andExpr);
}

std::unique_ptr<ast::Expression> Parser::relationalExprParser() {
    std::unique_ptr<RelationalExpr> relationalExpr = std::make_unique<RelationalExpr>(std::move(baseLogicParser()));

    std::unordered_map<TokenType, std::function<void()>> relationOp = {
            {TokenType::Equality,       [&]() { relationalExpr->addEquality(std::move(baseLogicParser())); }},
            {TokenType::Inequality,     [&]() { relationalExpr->addInequality(std::move(baseLogicParser())); }},
            {TokenType::Less,           [&]() { relationalExpr->addLess(std::move(baseLogicParser())); }},
            {TokenType::Greater,        [&]() { relationalExpr->addGreater(std::move(baseLogicParser())); }},
            {TokenType::LessOrEqual,    [&]() { relationalExpr->addLessOrEqual(std::move(baseLogicParser())); }},
            {TokenType::GreaterOrEqual, [&]() { relationalExpr->addGreaterOrEqual(std::move(baseLogicParser())); }}
    };

    if (relationOp.count(lexer->getToken().type)) {
        TokenType tokenType = lexer->getToken().type;
        lexer->readNextToken();
        relationOp.at(tokenType)();
    }

    return std::move(relationalExpr);
}

std::unique_ptr<ast::Expression> Parser::baseLogicParser() {
    if (accept(TokenType::Negation)) {
        return std::make_unique<BaseLogicExpr>(std::move(mathExprParser()), true);
    } else {
        return std::make_unique<BaseLogicExpr>(std::move(mathExprParser()));
    }
}

std::unique_ptr<ast::Expression> Parser::mathExprParser() {
    std::unique_ptr<MathExpr> mathExpr = std::make_unique<MathExpr>(std::move(multiplicativeExprParser()));
    Token token;

    std::unordered_map<TokenType, std::function<void()>> additiveOp = {
            {TokenType::Plus,  [&]() { mathExpr->addPlus(std::move(multiplicativeExprParser()), token.position); }},
            {TokenType::Minus, [&]() { mathExpr->addMinus(std::move(multiplicativeExprParser()), token.position); }}
    };

    while (additiveOp.count(lexer->getToken().type)) {
        token = lexer->getToken();
        lexer->readNextToken();
        additiveOp.at(token.type)();
    }

//    while (true) {
//        if (accept(TokenType::Plus)) {
//            mathExpr->addPlus(multiplicativeExprParser());
//        } else if (accept(TokenType::Minus)) {
//            mathExpr->addMinus(multiplicativeExprParser());
//        } else {
//            break;
//        }
//    }

    return std::move(mathExpr);
}

std::unique_ptr<ast::Expression> Parser::multiplicativeExprParser() {
    std::unique_ptr<MultiplicativeExpr> multiplicativeExpr = std::make_unique<MultiplicativeExpr>(
            std::move(baseMathExprParser()));
    Token token;

    std::unordered_map<TokenType, std::function<void()>> multiplicativeOp = {
            {TokenType::Multiply, [&]() {
                multiplicativeExpr->addMultiply(std::move(baseMathExprParser()), token.position);
            }},
            {TokenType::Divide,   [&]() {
                multiplicativeExpr->addDivide(std::move(baseMathExprParser()), token.position);
            }},
            {TokenType::Modulo,   [&]() {
                multiplicativeExpr->addModulo(std::move(baseMathExprParser()), token.position);
            }}
    };

    while (multiplicativeOp.count(lexer->getToken().type)) {
        token = lexer->getToken();
        lexer->readNextToken();
        multiplicativeOp.at(token.type)();
    }

    return std::move(multiplicativeExpr);
}

std::unique_ptr<ast::Expression> Parser::baseMathExprParser() {
    std::unique_ptr<BaseMathExpr> baseMathExpr;
    bool unaryMathOp = accept(TokenType::Minus);

    /*
     * NumberLiteral -> numberLiteral
     * Vec -> vectorLiteral
     * ParenthesisOpen -> expr <- parentExpr
     *
     * Identifier -> variable <- block
     * Identifier -> BracketOpen -> NumberLiteral -> BracketClose -> variable + index <- block
     * Identifier -> ParenthesisOpen -> arguments -> funCall
     * */

    Token tokenId = lexer->getToken();

    if (accept(TokenType::NumberLiteral, [&]() {
        //new Number
        baseMathExpr = std::make_unique<BaseMathExpr>(new Variable({std::stoi(lexer->getToken().value)}), unaryMathOp);
    })) {
    } else if (accept(TokenType::Vec)) {
        //new vector
        baseMathExpr = std::make_unique<BaseMathExpr>(new Variable(vectorLiteralParse()), unaryMathOp);
    } else if (accept(TokenType::ParenthesisOpen)) {
        baseMathExpr = std::make_unique<BaseMathExpr>(std::move(logicExprParse()), unaryMathOp);
        acceptOrThrow(TokenType::ParenthesisClose);
    } else if (accept(TokenType::Identifier)) {
        if (accept(TokenType::ParenthesisOpen)) {
            //funCall
            baseMathExpr = std::make_unique<BaseMathExpr>(std::move(functionCallParse(tokenId)), unaryMathOp);
        } else {
            //variable
            existVariable(tokenId);
            if (accept(TokenType::BracketOpen)) {
                //variable + index
                Token token;
                acceptOrThrow(TokenType::NumberLiteral, [&]() { token = lexer->getToken(); });
                acceptOrThrow(TokenType::BracketClose);

                baseMathExpr = std::make_unique<BaseMathExpr>(block->findVariable(tokenId.value, tokenId),
                                                              static_cast<unsigned int>(std::stoi(token.value)),
                                                              unaryMathOp);
                baseMathExpr->addPosition(token.position);
            } else {
                //variable
                baseMathExpr = std::make_unique<BaseMathExpr>(block->findVariable(tokenId.value, tokenId), unaryMathOp);
            }
        }
    } else {
        throwExpectedTokens({TokenType::NumberLiteral,
                             TokenType::Vec,
                             TokenType::ParenthesisOpen,
                             TokenType::Identifier});
    }

    return std::move(baseMathExpr);
}

ast::Variable Parser::vectorLiteralParse() {
    std::vector<int> variables;
    auto addNumberLiteral = [&]() {
        variables.push_back(std::stoi(lexer->getToken().value));
    };

    acceptOrThrow(TokenType::ParenthesisOpen);
    acceptOrThrow(TokenType::NumberLiteral, addNumberLiteral);
    acceptOrThrow(TokenType::Comma);
    acceptOrThrow(TokenType::NumberLiteral, addNumberLiteral);
    if (accept(TokenType::Comma)) {
        acceptOrThrow(TokenType::NumberLiteral, addNumberLiteral);
    }
    acceptOrThrow(TokenType::ParenthesisClose);

    return Variable(std::move(variables));
}

const bool Parser::existVariable(Token &tokenId) {
    if (!block->existVariable(tokenId.value)) {
        throw Exception(
                "Variable not found: " + tokenId.value +
                " at line: " + tokenId.position.toString());
    }
    return true;
}
