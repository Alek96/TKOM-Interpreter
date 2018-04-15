#ifndef INTERPRETER_BASEMATHEXPR_HPP
#define INTERPRETER_BASEMATHEXPR_HPP

#include "Variable.hpp"
#include "Expression.hpp"
#include <memory>

namespace tkom {
    namespace ast {

        class BaseMathExpr : public Expression {
        public:
            BaseMathExpr() = delete;
            explicit BaseMathExpr(Variable *literal, bool unaryMathOp = false);
            explicit BaseMathExpr(Variable& variable, bool unaryMathOp = false);
//        explicit BaseMathExpr(..., bool unaryMathOp = false)
            explicit BaseMathExpr(std::unique_ptr<Expression> expr, bool unaryMathOp = false);

            BaseMathExpr(const BaseMathExpr &other) = delete;
            BaseMathExpr(BaseMathExpr &&other) noexcept;

            ~BaseMathExpr() override;

            Variable calculate() override;

        private:
            bool unaryMathOp = false;
            Variable *literal = nullptr;
            Variable *variable = nullptr;
            //functionCall
//            Expression *parenthLogicExpr = nullptr;
            std::unique_ptr<Expression> parenthLogicExpr;
        };

    }
}

#endif //INTERPRETER_BASEMATHEXPR_HPP
