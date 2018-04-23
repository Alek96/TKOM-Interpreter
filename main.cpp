#include <iostream>
#include <memory>
#include <sstream>
#include "lexer/Lexer.hpp"
#include "parser/Parser.hpp"
#include "printer/Printer.hpp"

int main() {
    std::string streamValue = " ";
    std::stringstream stream(streamValue);
    tkom::Parser parser(std::make_unique<tkom::Lexer>(stream));
    stream << "function fun(a) {\n"
              "print(a);\n"
              "return 3;\n"
              "}\n"
              "function main() {\n"
              "fun(fun(2));\n"
              "}";
    parser.parse();
    parser.run();

    return 0;
}
