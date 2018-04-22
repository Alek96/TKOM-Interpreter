#ifndef INTERPRETER_FUNCTIONCALL_HPP
#define INTERPRETER_FUNCTIONCALL_HPP

#include <list>
#include <memory>
#include "Statement.hpp"
#include "ast/FunctionDef.hpp"
#include "ast/expression/Expression.hpp"
#include "ast/Variable.hpp"
#include "reader/SignPosition.hpp"

namespace tkom {
    namespace ast {

        class FunctionCall : public Statement {
        public:
            explicit FunctionCall(FunctionDef &functionDef)
                    : functionDef(functionDef) {
            }

            void addExpression(std::unique_ptr<Expression> expr) {
                expressions.push_back(std::move(expr));
            }

            const unsigned size() const {
                return expressions.size();
            }

            Return run() override {
                std::list<Variable> var;
                for (auto &&expression : expressions) {
                    var.push_back(expression->calculate());
                }

                return functionDef.run(var);
            }

        private:
            FunctionDef &functionDef;
            std::list<std::unique_ptr<Expression>> expressions;
        };

    }
}

#endif //INTERPRETER_FUNCTIONCALL_HPP
