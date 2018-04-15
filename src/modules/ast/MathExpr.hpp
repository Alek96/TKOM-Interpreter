#ifndef INTERPRETER_MATHEXPR_HPP
#define INTERPRETER_MATHEXPR_HPP

#include <list>
#include "Variable.hpp"
#include "Expression.hpp"
#include "MultiplicativeExpr.hpp"
#include "token/Token.hpp"

namespace tkom {
    namespace ast {

        class MathExpr : public Expression {
            using exprPtr = std::unique_ptr<Expression>;

        public:
            explicit MathExpr(exprPtr multiplicativeExpr);

            MathExpr(const MathExpr &) = delete;
            MathExpr(MathExpr &&rhs)noexcept;

            Variable calculate() override;

            void addPlus(exprPtr multiplicativeExpr);
            void addMinus(exprPtr multiplicativeExpr);

        private:
            std::list<exprPtr> multiplicativeExprs;
            std::list<tkom::TokenType> additiveOps;
        };
    }
}


#endif //INTERPRETER_MATHEXPR_HPP
