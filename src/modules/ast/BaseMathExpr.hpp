#ifndef INTERPRETER_BASEMATHEXPR_HPP
#define INTERPRETER_BASEMATHEXPR_HPP

#include "Variable.hpp"
#include "Expression.hpp"
#include "LogicExpr.hpp"
#include <utility>

namespace tkom {
    namespace ast {

        class LogicExpr;

        class BaseMathExpr : public Expression {
        public:
            BaseMathExpr() = default;
            explicit BaseMathExpr(Variable *literal, bool unaryMathOp = false);
            explicit BaseMathExpr(Variable& variable, bool unaryMathOp = false);
//        explicit BaseMathExpr(..., bool unaryMathOp = false)
            explicit BaseMathExpr(LogicExpr *expr, bool unaryMathOp = false);

            BaseMathExpr(const BaseMathExpr &other) = delete;
            BaseMathExpr(BaseMathExpr &&other) noexcept;

            ~BaseMathExpr() override;

            Variable calculate() override;

        private:
            bool unaryMathOp = false;
            Variable *literal = nullptr;
            Variable *variable = nullptr;
            //functionCall
            LogicExpr *parenthLogicExpr = nullptr;
        };

    }
}

#endif //INTERPRETER_BASEMATHEXPR_HPP
