#ifndef INTERPRETER_BASEMATHEXPR_HPP
#define INTERPRETER_BASEMATHEXPR_HPP

#include "modules/ast/Variable.hpp"
#include "Expression.hpp"
#include <memory>

namespace tkom {
    namespace ast {

        class BaseMathExpr : public Expression {
        public:
            BaseMathExpr() = delete;
            explicit BaseMathExpr(Variable *literal, bool unaryMathOp = false);
            explicit BaseMathExpr(Variable& variable, bool unaryMathOp = false);
            explicit BaseMathExpr(Variable&& variable, bool unaryMathOp = false) = delete;
            explicit BaseMathExpr(Variable& variable, unsigned int index, bool unaryMathOp = false);
            explicit BaseMathExpr(Variable&& variable, unsigned int index, bool unaryMathOp = false) = delete;
//        explicit BaseMathExpr(..., bool unaryMathOp = false)
            explicit BaseMathExpr(std::unique_ptr<Expression> expr, bool unaryMathOp = false);

            BaseMathExpr(const BaseMathExpr &other) = delete;
            BaseMathExpr(BaseMathExpr &&other) noexcept;

            ~BaseMathExpr() override;

            Variable calculate() const override;

        private:
            bool unaryMathOp = false;
            Variable *literal = nullptr;
            Variable *variable = nullptr;
            //functionCall
            std::unique_ptr<Expression> parenthLogicExpr;
            int index = -1;
        };

    }
}

#endif //INTERPRETER_BASEMATHEXPR_HPP
