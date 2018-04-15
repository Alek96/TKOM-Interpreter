#ifndef INTERPRETER_LOGICEXPR_HPP
#define INTERPRETER_LOGICEXPR_HPP

#include <vector>
#include "Variable.hpp"
#include "Expression.hpp"
#include "AndExpr.hpp"
#include "token/Token.hpp"

namespace tkom {
    namespace ast {

        class AndExpr;

        class LogicExpr : public Expression {
        public:
            explicit LogicExpr(AndExpr &&andExpr);

            LogicExpr(const LogicExpr &) = delete;
            LogicExpr(LogicExpr &&rhs)noexcept;

            Variable calculate() override;

            void addOr(AndExpr &&andExpr);

        private:
            std::vector<AndExpr> andExprs;
            std::vector<tkom::TokenType> orOps;
        };
    }
}

#endif //INTERPRETER_LOGICEXPR_HPP
