#ifndef INTERPRETER_ANDEXPR_HPP
#define INTERPRETER_ANDEXPR_HPP

#include <vector>
#include "Variable.hpp"
#include "Expression.hpp"
#include "RelationalExpr.hpp"
#include "token/Token.hpp"

namespace tkom {
    namespace ast {

        class AndExpr : public Expression {
        public:
            explicit AndExpr(RelationalExpr &&relationalExpr);

            AndExpr(const AndExpr &) = delete;
            AndExpr(AndExpr &&rhs)noexcept;

            Variable calculate() override;

            void addAnd(RelationalExpr &&relationalExpr);

        private:
            std::vector<RelationalExpr> relationalExprs;
            std::vector<tkom::TokenType> andOps;
        };

        AndExpr::AndExpr(RelationalExpr &&relationalExpr) {
            relationalExprs.push_back(std::move(relationalExpr));
        }

        AndExpr::AndExpr(AndExpr &&rhs) noexcept
            : relationalExprs(std::move(rhs.relationalExprs)),
              andOps(std::move(rhs.andOps)) {}

        Variable AndExpr::calculate() {
            if (relationalExprs.empty()) {
                return Variable();
            }
            Variable var = relationalExprs[0].calculate();
            for (int i = 1; i < relationalExprs.size(); ++i) {
                if (andOps[i - 1] == tkom::TokenType::And)
                    var = var && relationalExprs[i].calculate();
            }
            return var;
        }

        void AndExpr::addAnd(RelationalExpr &&relationalExpr) {
            relationalExprs.push_back(std::move(relationalExpr));
            andOps.push_back(tkom::TokenType::And);
        }

    }
}


#endif //INTERPRETER_ANDEXPR_HPP
