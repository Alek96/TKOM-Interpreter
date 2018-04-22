#ifndef INTERPRETER_ASSIGNSTATEMENT_HPP
#define INTERPRETER_ASSIGNSTATEMENT_HPP

#include <memory>
#include "Statement.hpp"
#include "ast/Variable.hpp"
#include "ast/expression/Expression.hpp"
#include "exception/Exception.hpp"

namespace tkom {
    namespace ast {

        class AssignStatement : public Statement {
        public:
            AssignStatement(Variable &variable, std::unique_ptr<Expression> expression)
                    : variable(variable), expression(std::move(expression)) {
            }
            AssignStatement(Variable &variable, const unsigned int index, std::unique_ptr<Expression> expression)
                    : variable(variable), expression(std::move(expression)), index(index) {
            }

            void setPosition(const SignPosition &sPos) {
                AssignStatement::sPos = sPos;
            }

            Return run() override {
                Variable ret = expression->calculate();
                if (index >= 0) {
                    if (ret.size() == 1) {
                        variable.setPosition(sPos);
                        variable.at(static_cast<unsigned int>(index)) = ret.at(0);
                    } else {
                        throw Exception("Try to assign a n-dimensional vector to the int "
                                        + (sPos != SignPosition() ? "at line: " + sPos.toString() : ""));
                    }
                } else {
                    variable = ret;
                }

                return Return(Return::_none);
            }

        private:
            Variable &variable;
            std::unique_ptr<Expression> expression;
            int index = -1;
            SignPosition sPos;
        };

    }
}

#endif //INTERPRETER_ASSIGNSTATEMENT_HPP
