#include "MultiplicativeExpr.hpp"

using namespace tkom::ast;


MultiplicativeExpr::MultiplicativeExpr(BaseMathExpr &&baseMathExpr) {
    baseMathExprs.push_back(std::move(baseMathExpr));
}

MultiplicativeExpr::MultiplicativeExpr(MultiplicativeExpr &&rhs) noexcept
        : baseMathExprs(std::move(rhs.baseMathExprs)),
          multiplicativeOps(std::move(rhs.multiplicativeOps)) {}

Variable MultiplicativeExpr::calculate() {
    if (baseMathExprs.empty()) {
        return Variable();
    }
    Variable var = baseMathExprs[0].calculate();
    for (unsigned int i = 1; i < baseMathExprs.size(); ++i) {
        if (multiplicativeOps[i - 1] == tkom::TokenType::Multiply)
            var = var * baseMathExprs[i].calculate();
        else if (multiplicativeOps[i - 1] == tkom::TokenType::Divide)
            var = var / baseMathExprs[i].calculate();
        else if (multiplicativeOps[i - 1] == tkom::TokenType::Modulo)
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