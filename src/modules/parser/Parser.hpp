#ifndef INTERPRETER_PARSER_HPP
#define INTERPRETER_PARSER_HPP

#include <memory>
#include "lexer/Lexer.hpp"

namespace tkom {

    class Parser {
    public:
        Parser(std::unique_ptr<Lexer> lexer);
        ~Parser() = default;

//        void parse();
    private:
        std::unique_ptr<Lexer> lexer;

//        void parseProgram();
    };
}

#endif //INTERPRETER_PARSER_HPP
