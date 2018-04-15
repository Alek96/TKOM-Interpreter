#ifndef INTERPRETER_MULTIPLICATIVEEXPR_HPP
#define INTERPRETER_MULTIPLICATIVEEXPR_HPP

#include <vector>
#include "Variable.hpp"
#include "Expression.hpp"
#include "BaseMathExpr.hpp"
#include "token/Token.hpp"

namespace tkom {
    namespace ast {

        class BaseMathExpr;

        class MultiplicativeExpr : public Expression {
        public:
            explicit MultiplicativeExpr(BaseMathExpr &&baseMathExpr);

            MultiplicativeExpr(const MultiplicativeExpr&) = delete;
            MultiplicativeExpr(MultiplicativeExpr &&rhs)noexcept;

            Variable calculate() override;

            void addMultiply(BaseMathExpr &&baseMathExpr);
            void addDivide(BaseMathExpr &&baseMathExpr);
            void addModulo(BaseMathExpr &&baseMathExpr);

        private:
            std::vector<BaseMathExpr> baseMathExprs;
            std::vector<tkom::TokenType> multiplicativeOps;
        };

    }
}


#endif //INTERPRETER_MULTIPLICATIVEEXPR_HPP
