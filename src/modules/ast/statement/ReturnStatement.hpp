#ifndef INTERPRETER_RETURNSTATEMENT_HPP
#define INTERPRETER_RETURNSTATEMENT_HPP

#include <memory>
#include "Statement.hpp"
#include "ast/expression/Expression.hpp"

namespace tkom {
    namespace ast {

        class ReturnStatement : public Statement {
        public:
            explicit ReturnStatement(std::unique_ptr<Expression> expression)
                    : expression(std::move(expression)) {
            }
            explicit ReturnStatement(Return::Type type)
                    : _return(type) {
            }

            Return run() override {
                if(expression) {
                    return Return(Return::_variable, expression->calculate());
                } else {
                    return Return(_return);
                }
            }

        private:
            std::unique_ptr<Expression> expression;
            Return::Type _return = Return::_none;
        };

    }
}

#endif //INTERPRETER_RETURNSTATEMENT_HPP
