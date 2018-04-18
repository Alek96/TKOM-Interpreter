#include "BaseMathExpr.hpp"

using namespace tkom::ast;

BaseMathExpr::BaseMathExpr(Variable *literal, bool unaryMathOp)
        : unaryMathOp(unaryMathOp),
          literal(literal) {
}

BaseMathExpr::BaseMathExpr(Variable &variable, bool unaryMathOp)
        : unaryMathOp(unaryMathOp),
          variable(&variable) {
}

BaseMathExpr::BaseMathExpr(Variable &variable, unsigned int index, bool unaryMathOp)
        : BaseMathExpr(new Variable({variable[index]}), unaryMathOp) {
}

BaseMathExpr::BaseMathExpr(std::unique_ptr<Expression> expr, bool unaryMathOp)
        : unaryMathOp(unaryMathOp),
          parenthLogicExpr(std::move(expr)) {
}

BaseMathExpr::BaseMathExpr(BaseMathExpr &&other) noexcept
        : unaryMathOp(other.unaryMathOp),
          literal(other.literal),
          variable(other.variable),
          parenthLogicExpr(std::move(other.parenthLogicExpr)) {

    other.unaryMathOp = false;
    other.literal = nullptr;
    //functionCall
//    other.parenthLogicExpr = nullptr;
}

BaseMathExpr::~BaseMathExpr() {
    delete literal;
//    delete parenthLogicExpr;
}

Variable BaseMathExpr::calculate() const {
    Variable currVar;
    if (literal) {
        currVar = *literal;
    } else if (variable) {
        if (index >= 0) {
            currVar = Variable({variable->at(static_cast<unsigned int>(index))});
        } else {
            currVar = *variable;
        }
    } else if (parenthLogicExpr) {
        currVar = parenthLogicExpr->calculate();
    }

    if (unaryMathOp) {
        currVar = -currVar;
    }
    return currVar;
}

