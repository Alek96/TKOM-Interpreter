#ifndef INTERPRETER_LOGICEXPR_HPP
#define INTERPRETER_LOGICEXPR_HPP

#include <list>
#include "modules/ast/Variable.hpp"
#include "Expression.hpp"
#include "AndExpr.hpp"
#include "modules/Token/Token.hpp"

namespace tkom {
    namespace ast {

        class LogicExpr : public Expression {
            using exprPtr = std::unique_ptr<Expression>;

        public:
            explicit LogicExpr(exprPtr andExpr);

            LogicExpr(const LogicExpr &) = delete;
            LogicExpr(LogicExpr &&rhs)noexcept;

            Variable calculate() const override;

            void addOr(exprPtr andExpr);

        private:
            std::list<exprPtr> andExprs;
        };
    }
}

#endif //INTERPRETER_LOGICEXPR_HPP
