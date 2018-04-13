#ifndef INTERPRETER_BASEMATHEXPR_HPP
#define INTERPRETER_BASEMATHEXPR_HPP

#include "Variable.hpp"
#include "Expression.hpp"
#include "LogicExpr.hpp"
#include <string>
#include <utility>

namespace tkom {
    namespace ast {

        class BaseMathExpr : public Expression {
        public:
            explicit BaseMathExpr(Variable *literal, bool unaryMathOp = false);
            explicit BaseMathExpr(std::string variable, bool unaryMathOp = false);
//        explicit BaseMathExpr(..., bool unaryMathOp = false)
            explicit BaseMathExpr(LogicExpr *expr, bool unaryMathOp = false);

            BaseMathExpr(const BaseMathExpr &other) = delete;
            BaseMathExpr(BaseMathExpr &&other) noexcept;

            ~BaseMathExpr() override;

            Variable calculate() override;

        private:
            bool unaryMathOp = false;
            Variable *literal = nullptr;
            std::string variable;
            //functionCall
            LogicExpr *parenthLogicExpr = nullptr;
        };


        BaseMathExpr::BaseMathExpr(Variable *literal, bool unaryMathOp)
                : unaryMathOp(unaryMathOp),
                  literal(literal) {}

        BaseMathExpr::BaseMathExpr(std::string variable, bool unaryMathOp)
                : unaryMathOp(unaryMathOp),
                  variable(std::move(variable)) {}

        BaseMathExpr::BaseMathExpr(LogicExpr *expr, bool unaryMathOp)
                : unaryMathOp(unaryMathOp),
                  parenthLogicExpr(expr) {}

        BaseMathExpr::BaseMathExpr(BaseMathExpr &&other) noexcept
                : unaryMathOp(other.unaryMathOp),
                  literal(other.literal),
                  variable(std::move(other.variable)),
                  parenthLogicExpr(other.parenthLogicExpr) {

            other.unaryMathOp = nullptr;
            other.literal = nullptr;
            //functionCall
            other.parenthLogicExpr = nullptr;
        }

        BaseMathExpr::~BaseMathExpr() {
            delete literal;
            delete parenthLogicExpr;
        }

        Variable BaseMathExpr::calculate() {
            Variable currVar;
            if (literal) {
                currVar = *literal;
            } else if (variable.empty()) {
                //find variable
            } else if(parenthLogicExpr) {
                currVar = parenthLogicExpr->calculate();
            } else {
                //exception
            }

            if (unaryMathOp) {
                currVar = -currVar;
            }
            return currVar;
        }

    }
}

#endif //INTERPRETER_BASEMATHEXPR_HPP
