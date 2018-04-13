#ifndef INTERPRETER_FUNTIONDEF_HPP
#define INTERPRETER_FUNTIONDEF_HPP

#include <vector>
#include <string>
#include "modules/ast/Statement.hpp"
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
            if(parameters.size() != var.size())
                return;
            for (int i = 0; i < parameters.size(); ++i) {
                block.addVariable(parameters[i], var[i]);
            }
            block.run();
        };

    private:
        const std::string identifier;
        std::vector<std::string> parameters;
        StatementBlock block;
    };
}
}

#endif //INTERPRETER_FUNTIONDEF_HPP
