#include "MathExpr.hpp"

using namespace tkom::ast;

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
    for (unsigned int i = 1; i < multiplicativeExprs.size(); ++i) {
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