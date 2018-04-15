#ifndef INTERPRETER_MATHEXPR_HPP
#define INTERPRETER_MATHEXPR_HPP

#include <vector>
#include "Variable.hpp"
#include "Expression.hpp"
#include "MultiplicativeExpr.hpp"
#include "token/Token.hpp"

namespace tkom {
    namespace ast {

        class MultiplicativeExpr;

        class MathExpr : public Expression {
        public:
            explicit MathExpr(MultiplicativeExpr &&multiplicativeExpr);

            MathExpr(const MathExpr &) = delete;
            MathExpr(MathExpr &&rhs)noexcept;

            Variable calculate() override;

            void addPlus(MultiplicativeExpr &&multiplicativeExpr);
            void addMinus(MultiplicativeExpr &&multiplicativeExpr);

        private:
            std::vector<MultiplicativeExpr> multiplicativeExprs;
            std::vector<tkom::TokenType> additiveOps;
        };
    }
}


#endif //INTERPRETER_MATHEXPR_HPP
