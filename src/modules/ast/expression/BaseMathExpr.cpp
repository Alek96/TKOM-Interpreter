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
        : unaryMathOp(unaryMathOp),
          variable(&variable),
          index(index) {
}

BaseMathExpr::BaseMathExpr(std::unique_ptr<Statement> functionCall, bool unaryMathOp)
        : unaryMathOp(unaryMathOp),
          functionCall(std::move(functionCall)) {
}


BaseMathExpr::BaseMathExpr(std::unique_ptr<Expression> expr, bool unaryMathOp)
        : unaryMathOp(unaryMathOp),
          parentLogicExpr(std::move(expr)) {
}

BaseMathExpr::BaseMathExpr(BaseMathExpr &&other) noexcept
        : unaryMathOp(other.unaryMathOp),
          literal(other.literal),
          variable(other.variable),
          functionCall(std::move(other.functionCall)),
          parentLogicExpr(std::move(other.parentLogicExpr)) {

    other.unaryMathOp = false;
    other.literal = nullptr;
}

BaseMathExpr::~BaseMathExpr() {
    delete literal;
}

Variable BaseMathExpr::calculate() const {
    Variable currVar;
    if (literal) {
        currVar = *literal;
    } else if (variable) {
        if (index >= 0) {
            if (!positions.empty()) {
                variable->setPosition(positions.front());
            }
            currVar = Variable({variable->at(static_cast<unsigned int>(index))});
        } else {
            currVar = *variable;
        }
    } else if (functionCall) {
        currVar = functionCall->run().variable;
    } else if (parentLogicExpr) {
        currVar = parentLogicExpr->calculate();
    }

    if (unaryMathOp) {
        currVar = -currVar;
    }
    return currVar;
}

