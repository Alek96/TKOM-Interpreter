#include "BaseMathExpr.hpp"

using namespace tkom::ast;

BaseMathExpr::BaseMathExpr(Variable *literal, bool unaryMathOp)
        : unaryMathOp(unaryMathOp),
          literal(literal) {}

BaseMathExpr::BaseMathExpr(Variable &variable, bool unaryMathOp)
        : unaryMathOp(unaryMathOp),
          variable(&variable) {}

BaseMathExpr::BaseMathExpr(LogicExpr *expr, bool unaryMathOp)
        : unaryMathOp(unaryMathOp),
          parenthLogicExpr(expr) {}

BaseMathExpr::BaseMathExpr(BaseMathExpr &&other) noexcept
        : unaryMathOp(other.unaryMathOp),
          literal(other.literal),
          variable(other.variable),
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
    } else if (variable) {
        currVar = *variable;
    } else if(parenthLogicExpr) {
        currVar = parenthLogicExpr->calculate();
    }

    if (unaryMathOp) {
        currVar = -currVar;
    }
    return currVar;
}