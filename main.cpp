#include <iostream>
#include <memory>
#include <sstream>
#include <fstream>
#include "lexer/Lexer.hpp"
#include "parser/Parser.hpp"
#include "printer/Printer.hpp"
#include "library/Library.hpp"
#include "exception/Exception.hpp"

int main(int argc, char** argv) {
    tkom::Parser parser;
    tkom::Library library(parser);
    std::fstream file;
    tkom::Printer::instance().setEnableOutput(true);

    if(argc == 2) {
        file.open(argv[1], std::ios::in);
        if(!file.good()) {
            std::cout << "file not found\n";
            return -1;
        }
        try {
            parser.setLexer(std::make_unique<tkom::Lexer>(file));
            parser.parse();
            parser.run();
        } catch (tkom::Exception &e) {
            //std::cout << e.what() << std::endl;
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
        file.close();
    } else {
        std:: cout << "Put file path in argument\n";
    }

    return 0;
}
