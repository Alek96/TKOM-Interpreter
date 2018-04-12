#ifndef INTERPRETER_AST_STATEMENTBLOCK_HPP
#define INTERPRETER_AST_STATEMENTBLOCK_HPP

#include <vector>
#include <unordered_map>
#include <string>
#include "../AST.hpp"
#include "Variable.hpp"

namespace tkom { namespace ast {

    class StatementBlock : public Node {
    public:
        explicit StatementBlock(const StatementBlock *block = nullptr) : block(block) {}
        StatementBlock(const StatementBlock &) = delete;
        ~StatementBlock() override {
            for (auto &variable : variables) {
                delete variable.second;
            }
        }

//        StatementBlock &operator=(StatementBlock &) = delete;
        StatementBlock &operator=(StatementBlock &&other) = default;

        void addInstruction(const Node &node) {
            this->instructions.push_back(node);
        }
        void addVariable(const std::string& identifier, Variable* variable) {
            variables.insert({identifier, variable});
        }


        void run() override {
            for (auto &&instruction : instructions) {
                instruction.run();
            }
        };

    private:
        const StatementBlock *block;
        std::vector<Node> instructions;
        std::unordered_map<std::string, Variable*> variables;
    };

}
}

#endif //INTERPRETER_STATEMENTBLOCK_HPP
