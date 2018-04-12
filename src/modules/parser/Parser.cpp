#include "Parser.hpp"

using namespace tkom;

Parser::Parser(std::unique_ptr<Lexer> lexer_)
        : lexer(std::move(lexer_)){}
