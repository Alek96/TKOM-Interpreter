#include "BaseLogicExpr.hpp"

using namespace tkom::ast;

BaseLogicExpr::BaseLogicExpr(exprPtr mathExpr, bool unaryLogicOp)
        : /*mathExpr(std::move(mathExpr)),*/
        unaryLogicOp(unaryLogicOp) {
    mathExprs.push_back(std::move(mathExpr));
}

BaseLogicExpr::BaseLogicExpr(BaseLogicExpr &&rhs) noexcept
        : mathExprs(std::move(rhs.mathExprs)),
          unaryLogicOp(rhs.unaryLogicOp) {

        }

Variable BaseLogicExpr::calculate() {
    return unaryLogicOp ? !mathExprs.begin()->get()->calculate() : mathExprs.begin()->get()->calculate();
}
