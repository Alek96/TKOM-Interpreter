#include "MathExpr.hpp"
#include "exception/Exception.hpp"

using namespace tkom::ast;

MathExpr::MathExpr(exprPtr multiplicativeExpr) {
    multiplicativeExprs.push_back(std::move(multiplicativeExpr));
}

MathExpr::MathExpr(MathExpr &&rhs) noexcept
        : multiplicativeExprs(std::move(rhs.multiplicativeExprs)),
          additiveOps(std::move(rhs.additiveOps)) {}

Variable MathExpr::calculate() {
    auto itExpr = multiplicativeExprs.begin();
    Variable var = itExpr->get()->calculate();

    for (auto &&op : additiveOps) {
        ++itExpr;
        if (op == tkom::TokenType::Plus)
            var = var + itExpr->get()->calculate();
        else if (op == tkom::TokenType::Minus)
            var = var - itExpr->get()->calculate();
        else
            throw Exception("Bad TokenType in additiveOps");
    }

    return var;
}

void MathExpr::addPlus(exprPtr multiplicativeExpr) {
    multiplicativeExprs.push_back(std::move(multiplicativeExpr));
    additiveOps.push_back(tkom::TokenType::Plus);
}

void MathExpr::addMinus(exprPtr multiplicativeExpr) {
    multiplicativeExprs.push_back(std::move(multiplicativeExpr));
    additiveOps.push_back(tkom::TokenType::Minus);
}