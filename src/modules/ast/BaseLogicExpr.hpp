#ifndef INTERPRETER_BASELOGICEXPR_HPP
#define INTERPRETER_BASELOGICEXPR_HPP

#include <vector>
#include "Variable.hpp"
#include "Expression.hpp"
#include "MathExpr.hpp"
#include "token/Token.hpp"

namespace tkom {
    namespace ast {

        class MathExpr;

        class BaseLogicExpr : public Expression {
        public:
            explicit BaseLogicExpr(MathExpr &&mathExpr, bool unaryLogicOp);

            BaseLogicExpr(const BaseLogicExpr &) = delete;
            BaseLogicExpr(BaseLogicExpr &&rhs)noexcept;

            Variable calculate() override;

        private:
            std::vector<MathExpr> mathExprs;
            bool unaryLogicOp = false;
        };
    }
}


#endif //INTERPRETER_BASELOGICEXPR_HPP
