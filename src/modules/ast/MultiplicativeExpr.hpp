#ifndef INTERPRETER_MULTIPLICATIVEEXPR_HPP
#define INTERPRETER_MULTIPLICATIVEEXPR_HPP

#include <list>
#include <memory>
#include "Variable.hpp"
#include "Expression.hpp"
#include "BaseMathExpr.hpp"
#include "token/Token.hpp"

namespace tkom {
    namespace ast {

        class MultiplicativeExpr : public Expression {
            using exprPtr = std::unique_ptr<Expression>;

        public:
            MultiplicativeExpr() = delete;
            explicit MultiplicativeExpr(exprPtr baseMathExpr);

            MultiplicativeExpr(const MultiplicativeExpr&) = delete;
            MultiplicativeExpr(MultiplicativeExpr &&rhs)noexcept;

            Variable calculate() override;

            void addMultiply(exprPtr baseMathExpr);
            void addDivide(exprPtr baseMathExpr);
            void addModulo(exprPtr baseMathExpr);

        private:
            std::list<exprPtr> baseMathExprs;
            std::list<tkom::TokenType> multiplicativeOps;
        };

    }
}


#endif //INTERPRETER_MULTIPLICATIVEEXPR_HPP
