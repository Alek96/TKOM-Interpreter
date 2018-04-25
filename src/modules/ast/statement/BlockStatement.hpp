#ifndef INTERPRETER_AST_STATEMENTBLOCK_HPP
#define INTERPRETER_AST_STATEMENTBLOCK_HPP

#include <list>
#include <unordered_map>
#include <string>
#include "Statement.hpp"
#include "modules/ast/Variable.hpp"
#include "exception/Exception.hpp"

namespace tkom {
    namespace ast {

        class BlockStatement : public Statement {
            using statBlockPtr = std::unique_ptr<Statement>;

        public:
            explicit BlockStatement(BlockStatement *parentBlock = nullptr) : parentBlock(parentBlock) {}

            BlockStatement(const BlockStatement &) = delete;

            BlockStatement &operator=(BlockStatement &) = delete;

            BlockStatement &operator=(BlockStatement &&other) = default;

            const BlockStatement *getParentBlock() const {
                return parentBlock;
            }

            void addInstruction(statBlockPtr statement) {
                this->instructions.push_back(std::move(statement));
            }

//            Statement& getLastInstruction() {
//                return *(*--instructions.end());
//            }
//            void addVariable(const std::string &identifier, Variable &variable) {
//                variables.insert({identifier, std::move(variable)});
//            }
            void addVariable(const std::string &identifier, Variable &&variable) {
                variables.insert({identifier, std::move(variable)});
            }

            Variable &findVariable(const std::string &identifier, Token tokenId = Token()) {
                if (variables.count(identifier)) {
                    return variables.at(identifier);
                } else if(parentBlock){
                    return parentBlock->findVariable(identifier);
                }
                throw Exception("Variable not found "
                                " at line: " + tokenId.position.toString());
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
            BlockStatement *parentBlock;
            std::list<statBlockPtr> instructions;
            std::unordered_map<std::string, Variable> variables;
        };

    }
}

#endif //INTERPRETER_STATEMENTBLOCK_HPP
