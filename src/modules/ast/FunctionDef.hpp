#ifndef INTERPRETER_FUNTIONDEF_HPP
#define INTERPRETER_FUNTIONDEF_HPP

#include <list>
#include <string>
#include "statement/Statement.hpp"
#include "modules/ast/statement/BlockStatement.hpp"
#include "Variable.hpp"
#include "exception/Exception.hpp"

namespace tkom {
    namespace ast {

        class FunctionDef {
        public:
            explicit FunctionDef(std::string &identifier) : identifier(identifier) {}

            void addParameter(const std::string &identifier) {
                parameters.push_back(identifier);
                functionBlock.addVariable(identifier, Variable());
            }

            const std::string &getIdentifier() const { return identifier; }

            unsigned size() { return parameters.size(); }

            const unsigned size() const { return parameters.size(); }

            BlockStatement &getFunctionBlock() {
                return functionBlock;
            }

            Return run(std::list<Variable> &var) {
                auto itParameters = parameters.begin();
                auto itVar = var.begin();

                for (; itVar != var.end(); ++itVar, ++itParameters) {
                    functionBlock.findVariable(*itParameters) = *itVar;
                }
                Return ret = functionBlock.run();

                return ret;
            };

        private:
            const std::string identifier;
            std::list<std::string> parameters;
            BlockStatement functionBlock;
        };
    }
}

#endif //INTERPRETER_FUNTIONDEF_HPP
