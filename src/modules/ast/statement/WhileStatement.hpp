#ifndef INTERPRETER_WHILESTATEMENT_HPP
#define INTERPRETER_WHILESTATEMENT_HPP

#include <iostream>
#include "Statement.hpp"
#include "ast/expression/Expression.hpp"
#include "BlockStatement.hpp"
#include "exception/Exception.hpp"

namespace tkom {
    namespace ast {

        class WhileStatement : public Statement {
        public:
            WhileStatement(std::unique_ptr<Expression> expression,
                           std::unique_ptr<BlockStatement> block)
                    : expression(std::move(expression)),
                      block(std::move(block)) {
            }

            Return run() override {
                Return ret;
                unsigned int time = 1000 * 1000 * 1;

                while (expression->calculate() && time--) {
                    ret = block->run();

                    switch (ret.type) {
                        case Return::_break:
                            return Return(Return::_none);

                        case Return::_variable:
                            return ret;

                        default:
                            continue;
                    }
                }
                if (!time)
                    throw Exception("Run time");
                else {
                    return Return(Return::_none);
                }
            }

        private:
            std::unique_ptr<Expression> expression;
            std::unique_ptr<BlockStatement> block;
        };

    }
}

#endif //INTERPRETER_WHILESTATEMENT_HPP
