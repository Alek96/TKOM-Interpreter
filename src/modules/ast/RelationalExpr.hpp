#ifndef INTERPRETER_RELATIONALEXPR_HPP
#define INTERPRETER_RELATIONALEXPR_HPP

#include <list>
#include "Variable.hpp"
#include "Expression.hpp"
#include "BaseLogicExpr.hpp"
#include "token/Token.hpp"

namespace tkom {
    namespace ast {

        class RelationalExpr : public Expression {
            using exprPtr = std::unique_ptr<Expression>;

        public:
            explicit RelationalExpr(exprPtr baseLogicExpr);

            RelationalExpr(const RelationalExpr &) = delete;
            RelationalExpr(RelationalExpr &&rhs)noexcept;

            Variable calculate() override;

            void addEquality(exprPtr baseLogicExpr);
            void addInequality(exprPtr baseLogicExpr);

            void addLess(exprPtr baseLogicExpr);
            void addGreater(exprPtr baseLogicExpr);

            void addLessOrEqual(exprPtr baseLogicExpr);
            void addGreaterOrEqual(exprPtr baseLogicExpr);

        private:
            std::list<exprPtr> baseLogicExprs;
            std::list<tkom::TokenType> relationOps;
        };
    }
}


#endif //INTERPRETER_RELATIONALEXPR_HPP
