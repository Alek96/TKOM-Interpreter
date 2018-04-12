#ifndef INTERPRETER_FUNTIONDEF_HPP
#define INTERPRETER_FUNTIONDEF_HPP

#include <vector>
#include <string>
#include "../AST.hpp"
#include "StatementBlock.hpp"
#include "Variable.hpp"

namespace tkom { namespace ast {

    class FunctionDef {
    public:
        explicit FunctionDef(std::string& identifier) : identifier(identifier) {}
        void addParameter(const std::string& identifier) {
            parameters.push_back(identifier);
        }
        void setStatementBlock(StatementBlock& block) {
            block = move(block);
        }

        void run(std::vector<Variable> var) {
            //statementBlock add variables
            //statementBlock run
        };

    private:
        const std::string identifier;
        std::vector<std::string> parameters;
        StatementBlock block;
    };
}
}

#endif //INTERPRETER_FUNTIONDEF_HPP

///variables inaczej zrobic
///wyrazenia matematyczne nie działaja