#ifndef INTERPRETER_PROGRAM_HPP
#define INTERPRETER_PROGRAM_HPP

#include <vector>
#include "../AST.hpp"
#include "FunctionDef.hpp"

namespace tkom { namespace ast {

    class Program {
    public:
        void addFunction(const FunctionDef &function) {
            functions.push_back(function);
        }

        void run() {
            for (auto &&function : functions) {
                function.run();
            }
        };

    private:
        std::vector<FunctionDef> functions;
    };
}
}

#endif //INTERPRETER_PROGRAM_HPP
