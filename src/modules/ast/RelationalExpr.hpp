#ifndef INTERPRETER_RELATIONALEXPR_HPP
#define INTERPRETER_RELATIONALEXPR_HPP

#include <vector>
#include "Variable.hpp"
#include "Expression.hpp"
#include "BaseMathExpr.hpp"
#include "token/Token.hpp"

namespace tkom {
    namespace ast {

        class RelationalExpr : public Expression {
        public:
            explicit RelationalExpr(BaseMathExpr &&baseMathExpr);

            RelationalExpr(const RelationalExpr &) = delete;
            RelationalExpr(RelationalExpr &&rhs)noexcept;

            Variable calculate() override;

            void addEquality(BaseMathExpr &&baseMathExpr);
            void addInequality(BaseMathExpr &&baseMathExpr);

            void addLess(BaseMathExpr &&baseMathExpr);
            void addGreater(BaseMathExpr &&baseMathExpr);

            void addLessOrEqual(BaseMathExpr &&baseMathExpr);
            void addGreaterOrEqual(BaseMathExpr &&baseMathExpr);

        private:
            std::vector<BaseMathExpr> baseMathExprs;
            std::vector<tkom::TokenType> relationOps;
        };

        RelationalExpr::RelationalExpr(BaseMathExpr &&baseMathExpr) {
            baseMathExprs.push_back(std::move(baseMathExpr));
        }

        RelationalExpr::RelationalExpr(RelationalExpr &&rhs) noexcept
                : baseMathExprs(std::move(rhs.baseMathExprs)),
                  relationOps(std::move(rhs.relationOps)) {}

        Variable RelationalExpr::calculate() {
            if (baseMathExprs.empty()) {
                return Variable();
            }
            Variable var = baseMathExprs[0].calculate();
            for (int i = 1; i < baseMathExprs.size(); ++i) {
                if (relationOps[i - 1] == tkom::TokenType::Equality)
                    var = var == baseMathExprs[i].calculate();
                else if (relationOps[i - 1] == tkom::TokenType::Inequality)
                    var = var != baseMathExprs[i].calculate();
                else if (relationOps[i - 1] == tkom::TokenType::Less)
                    var = var < baseMathExprs[i].calculate();
                else if (relationOps[i - 1] == tkom::TokenType::Greater)
                    var = var > baseMathExprs[i].calculate();
                else if (relationOps[i - 1] == tkom::TokenType::LessOrEqual)
                    var = var <= baseMathExprs[i].calculate();
                else if (relationOps[i - 1] == tkom::TokenType::GreaterOrEqual)
                    var = var >= baseMathExprs[i].calculate();
            }
            return var;
        }

        void RelationalExpr::addEquality(BaseMathExpr &&baseMathExpr) {
            baseMathExprs.push_back(std::move(baseMathExprs));
            relationOps.push_back(tkom::TokenType::Equality);
        }

        void RelationalExpr::addInequality(BaseMathExpr &&baseMathExpr) {
            baseMathExprs.push_back(std::move(baseMathExprs));
            relationOps.push_back(tkom::TokenType::Inequality);
        }

        void RelationalExpr::addLess(BaseMathExpr &&baseMathExpr) {
            baseMathExprs.push_back(std::move(baseMathExprs));
            relationOps.push_back(tkom::TokenType::Less);
        }

        void RelationalExpr::addGreater(BaseMathExpr &&baseMathExpr) {
            baseMathExprs.push_back(std::move(baseMathExprs));
            relationOps.push_back(tkom::TokenType::Greater);
        }

        void RelationalExpr::addLessOrEqual(BaseMathExpr &&baseMathExpr) {
            baseMathExprs.push_back(std::move(baseMathExprs));
            relationOps.push_back(tkom::TokenType::LessOrEqual);
        }

        void RelationalExpr::addGreaterOrEqual(BaseMathExpr &&baseMathExpr) {
            baseMathExprs.push_back(std::move(baseMathExprs));
            relationOps.push_back(tkom::TokenType::GreaterOrEqual);
        }
    }
}


#endif //INTERPRETER_RELATIONALEXPR_HPP
