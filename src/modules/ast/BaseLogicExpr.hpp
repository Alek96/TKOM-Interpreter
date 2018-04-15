#ifndef INTERPRETER_BASELOGICEXPR_HPP
#define INTERPRETER_BASELOGICEXPR_HPP

#include <list>
#include "Variable.hpp"
#include "Expression.hpp"
#include "MathExpr.hpp"
#include "token/Token.hpp"

namespace tkom {
    namespace ast {

        class BaseLogicExpr : public Expression {
            using exprPtr = std::unique_ptr<Expression>;

        public:
            explicit BaseLogicExpr(exprPtr mathExpr, bool unaryLogicOp = false);

            BaseLogicExpr(const BaseLogicExpr &) = delete;
            BaseLogicExpr(BaseLogicExpr &&rhs)noexcept;

            Variable calculate() override;

        private:
            std::list<exprPtr> mathExprs;
            bool unaryLogicOp = false;
        };
    }
}


#endif //INTERPRETER_BASELOGICEXPR_HPP
