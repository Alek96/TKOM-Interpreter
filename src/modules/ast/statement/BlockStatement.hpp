#ifndef INTERPRETER_AST_STATEMENTBLOCK_HPP
#define INTERPRETER_AST_STATEMENTBLOCK_HPP

#include <list>
#include <unordered_map>
#include <string>
#include "Statement.hpp"
#include "modules/ast/Variable.hpp"

namespace tkom {
    namespace ast {

        class BlockStatement : public Statement {
            using statBlockPtr = std::unique_ptr<Statement>;

        public:
            explicit BlockStatement(const BlockStatement *parentBlock = nullptr) : parentBlock(parentBlock) {}
            BlockStatement(const BlockStatement &) = delete;

            BlockStatement &operator=(BlockStatement &) = delete;
            BlockStatement &operator=(BlockStatement &&other) = default;

            void addInstruction(statBlockPtr statement) {
                this->instructions.push_back(std::move(statement));
            }

            void addVariable(const std::string &identifier, Variable &variable) {
                variables.insert({identifier, std::move(variable)});
            }
            void addVariable(const std::string &identifier, Variable &&variable) {
                variables.insert({identifier, std::move(variable)});
            }

            Variable& findVariable(std::string &identifier) {
                return variables.at(identifier);
            }

            void eraseVariable(const std::string &identifier) {
                variables.erase(identifier);
            }

            const bool existVariable(const std::string &identifier) const {
                return variables.count(identifier) || (parentBlock ? parentBlock->existVariable(identifier) : false);
            }

            Return run() override {
                Return ret;
                for (auto &&instruction : instructions) {
                    ret = instruction->run();
                    if (ret.type != Return::_none)
                        break;
                }
                return ret;
            };

        private:
            const BlockStatement *parentBlock;
            std::list<statBlockPtr> instructions;
            std::unordered_map<std::string, Variable> variables;
        };

    }
}

#endif //INTERPRETER_STATEMENTBLOCK_HPP
