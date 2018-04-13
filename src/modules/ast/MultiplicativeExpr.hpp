#ifndef INTERPRETER_MULTIPLICATIVEEXPR_HPP
#define INTERPRETER_MULTIPLICATIVEEXPR_HPP

#include <vector>
#include "Variable.hpp"
#include "Expression.hpp"
#include "BaseMathExpr.hpp"
#include "token/Token.hpp"

namespace tkom {
    namespace ast {

        class MultiplicativeExpr : public Expression {
        public:
            explicit MultiplicativeExpr(BaseMathExpr &&baseMathExpr);

            MultiplicativeExpr(const MultiplicativeExpr&) = delete;
            MultiplicativeExpr(MultiplicativeExpr &&rhs)noexcept;

            Variable calculate() override;

            void addMultiply(BaseMathExpr &&baseMathExpr);
            void addDivide(BaseMathExpr &&baseMathExpr);
            void addModulo(BaseMathExpr &&baseMathExpr);

        private:
            std::vector<BaseMathExpr> baseMathExprs;
            std::vector<tkom::TokenType> multiplicativeOps;
        };


        MultiplicativeExpr::MultiplicativeExpr(BaseMathExpr &&baseMathExpr) {
            baseMathExprs.push_back(std::move(baseMathExpr));
        }

        MultiplicativeExpr::MultiplicativeExpr(MultiplicativeExpr &&rhs) noexcept
                : baseMathExprs(std::move(rhs.baseMathExprs)),
                  multiplicativeOps(std::move(rhs.multiplicativeOps)) {}

        Variable MultiplicativeExpr::calculate()  {
            if(baseMathExprs.empty()) {
                return Variable();
            }
            Variable var = baseMathExprs[0].calculate();
            for (int i = 1; i < baseMathExprs.size(); ++i) {
                if(multiplicativeOps[i-1] == tkom::TokenType::Multiply)
                    var = var * baseMathExprs[i].calculate();
                else if(multiplicativeOps[i-1] == tkom::TokenType::Divide)
                    var = var / baseMathExprs[i].calculate();
                else if(multiplicativeOps[i-1] == tkom::TokenType::Modulo)
                    var = var % baseMathExprs[i].calculate();
            }
            return var;
        }

        void MultiplicativeExpr::addMultiply(BaseMathExpr &&baseMathExpr) {
            baseMathExprs.push_back(std::move(baseMathExpr));
            multiplicativeOps.push_back(tkom::TokenType::Multiply);
        }

        void MultiplicativeExpr::addDivide(BaseMathExpr &&baseMathExpr) {
            baseMathExprs.push_back(std::move(baseMathExpr));
            multiplicativeOps.push_back(tkom::TokenType::Divide);
        }

        void MultiplicativeExpr::addModulo(BaseMathExpr &&baseMathExpr) {
            baseMathExprs.push_back(std::move(baseMathExpr));
            multiplicativeOps.push_back(tkom::TokenType::Modulo);
        }

    }
}


#endif //INTERPRETER_MULTIPLICATIVEEXPR_HPP
