#ifndef INTERPRETER_IFSTATEMENT_HPP
#define INTERPRETER_IFSTATEMENT_HPP

#include <memory>
#include "Statement.hpp"
#include "BlockStatement.hpp"
#include "ast/expression/Expression.hpp"

namespace tkom {
    namespace ast {

        class IfStatement : public BlockStatement {
        public:
            IfStatement(std::unique_ptr<Expression> expression,
                        std::unique_ptr<BlockStatement> ifBlock)
                    : expression(std::move(expression)),
                      ifBlock(std::move(ifBlock)) {
            }

            IfStatement(std::unique_ptr<Expression> expression,
                        std::unique_ptr<BlockStatement> ifBlock,
                        std::unique_ptr<BlockStatement> elseBlock)
                    : IfStatement(std::move(expression), std::move(ifBlock)) {
                this->elseBlock = std::move(elseBlock);
            }

            Return run() override {
                if (expression->calculate()) {
                    return ifBlock->run();
                } else {
                    if (elseBlock) {
                        return elseBlock->run();
                    } else {
                        return Return(Return::_none);
                    }
                }
            }

        private:
            std::unique_ptr<Expression> expression;
            std::unique_ptr<BlockStatement> ifBlock;
            std::unique_ptr<BlockStatement> elseBlock;
        };

    }
}


#endif //INTERPRETER_IFSTATEMENT_HPP
