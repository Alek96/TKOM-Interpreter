#ifndef INTERPRETER_BASELOGICEXPR_HPP
#define INTERPRETER_BASELOGICEXPR_HPP

#include <vector>
#include "Variable.hpp"
#include "Expression.hpp"
#include "MathExpr.hpp"
#include "token/Token.hpp"

namespace tkom {
    namespace ast {

        class BaseLogicExpr : public Expression {
        public:
            explicit BaseLogicExpr(MathExpr &&mathExpr, bool unaryLogicOp);

            BaseLogicExpr(const BaseLogicExpr &) = delete;
            BaseLogicExpr(BaseLogicExpr &&rhs)noexcept;

            Variable calculate() override;

        private:
            MathExpr mathExpr;
            bool unaryLogicOp = false;
        };

        BaseLogicExpr::BaseLogicExpr(MathExpr &&mathExpr, bool unaryLogicOp)
                : mathExpr(std::move(mathExpr)),
                  unaryLogicOp(unaryLogicOp){}

        BaseLogicExpr::BaseLogicExpr(BaseLogicExpr &&rhs) noexcept
                : mathExpr(std::move(rhs.mathExpr)),
                  unaryLogicOp(rhs.unaryLogicOp) {}

        Variable BaseLogicExpr::calculate() {
            return unaryLogicOp ? !mathExpr.calculate() : mathExpr.calculate();
        }
    }
}


#endif //INTERPRETER_BASELOGICEXPR_HPP
