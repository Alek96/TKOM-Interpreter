#ifndef INTERPRETER_MATHEXPR_HPP
#define INTERPRETER_MATHEXPR_HPP

#include <vector>
#include "Variable.hpp"
#include "Expression.hpp"
#include "MultiplicativeExpr.hpp"
#include "token/Token.hpp"

namespace tkom {
    namespace ast {

        class MathExpr : public Expression {
        public:
            explicit MathExpr(MultiplicativeExpr &&multiplicativeExpr);

            MathExpr(const MathExpr &) = delete;
            MathExpr(MathExpr &&rhs)noexcept;

            Variable calculate() override;

            void addPlus(MultiplicativeExpr &&multiplicativeExpr);
            void addMinus(MultiplicativeExpr &&multiplicativeExpr);

        private:
            std::vector<MultiplicativeExpr> multiplicativeExprs;
            std::vector<tkom::TokenType> additiveOps;
        };


        MathExpr::MathExpr(MultiplicativeExpr &&multiplicativeExpr) {
            multiplicativeExprs.push_back(std::move(multiplicativeExpr));
        }

        MathExpr::MathExpr(MathExpr &&rhs) noexcept
                : multiplicativeExprs(std::move(rhs.multiplicativeExprs)),
                  additiveOps(std::move(rhs.additiveOps)) {}

        Variable MathExpr::calculate() {
            if (multiplicativeExprs.empty()) {
                return Variable();
            }
            Variable var = multiplicativeExprs[0].calculate();
            for (int i = 1; i < multiplicativeExprs.size(); ++i) {
                if (additiveOps[i - 1] == tkom::TokenType::Plus)
                    var = var + multiplicativeExprs[i].calculate();
                else if (additiveOps[i - 1] == tkom::TokenType::Minus)
                    var = var - multiplicativeExprs[i].calculate();
            }
            return var;
        }

        void MathExpr::addPlus(MultiplicativeExpr &&multiplicativeExpr) {
            multiplicativeExprs.push_back(std::move(multiplicativeExpr));
            additiveOps.push_back(tkom::TokenType::Plus);
        }

        void MathExpr::addMinus(MultiplicativeExpr &&multiplicativeExpr) {
            multiplicativeExprs.push_back(std::move(multiplicativeExpr));
            additiveOps.push_back(tkom::TokenType::Minus);
        }

    }
}


#endif //INTERPRETER_MATHEXPR_HPP
