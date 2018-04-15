#ifndef INTERPRETER_RELATIONALEXPR_HPP
#define INTERPRETER_RELATIONALEXPR_HPP

#include <vector>
#include "Variable.hpp"
#include "Expression.hpp"
#include "BaseLogicExpr.hpp"
#include "token/Token.hpp"

namespace tkom {
    namespace ast {

        class BaseLogicExpr;

        class RelationalExpr : public Expression {
        public:
            explicit RelationalExpr(BaseLogicExpr &&baseLogicExpr);

            RelationalExpr(const RelationalExpr &) = delete;
            RelationalExpr(RelationalExpr &&rhs)noexcept;

            Variable calculate() override;

            void addEquality(BaseLogicExpr &&baseLogicExpr);
            void addInequality(BaseLogicExpr &&baseLogicExpr);

            void addLess(BaseLogicExpr &&baseLogicExpr);
            void addGreater(BaseLogicExpr &&baseLogicExpr);

            void addLessOrEqual(BaseLogicExpr &&baseLogicExpr);
            void addGreaterOrEqual(BaseLogicExpr &&baseLogicExpr);

        private:
            std::vector<BaseLogicExpr> baseLogicExprs;
            std::vector<tkom::TokenType> relationOps;
        };
    }
}


#endif //INTERPRETER_RELATIONALEXPR_HPP
