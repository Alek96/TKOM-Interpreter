#ifndef INTERPRETER_LOGICEXPR_HPP
#define INTERPRETER_LOGICEXPR_HPP

#include <vector>
#include "Variable.hpp"
#include "Expression.hpp"
#include "AndExpr.hpp"
#include "token/Token.hpp"

namespace tkom {
    namespace ast {

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

        LogicExpr::LogicExpr(AndExpr &&andExpr) {
            andExprs.push_back(std::move(andExpr));
        }

        LogicExpr::LogicExpr(LogicExpr &&rhs) noexcept
                : andExprs(std::move(rhs.andExprs)),
                  orOps(std::move(rhs.orOps)) {}

        Variable LogicExpr::calculate() {
            if (andExprs.empty()) {
                return Variable();
            }
            Variable var = andExprs[0].calculate();
            for (int i = 1; i < andExprs.size(); ++i) {
                if (orOps[i - 1] == tkom::TokenType::Or)
                    var = var && andExprs[i].calculate();
            }
            return var;
        }

        void LogicExpr::addOr(AndExpr &&andExpr) {
            andExprs.push_back(std::move(andExpr));
            orOps.push_back(tkom::TokenType::Or);
        }

    }
}

#endif //INTERPRETER_LOGICEXPR_HPP
