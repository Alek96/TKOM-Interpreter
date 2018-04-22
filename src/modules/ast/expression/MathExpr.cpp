#include "MathExpr.hpp"
#include "exception/Exception.hpp"

using namespace tkom;
using namespace tkom::ast;

MathExpr::MathExpr(exprPtr multiplicativeExpr) {
    multiplicativeExprs.push_back(std::move(multiplicativeExpr));
}

MathExpr::MathExpr(MathExpr &&rhs) noexcept
        : multiplicativeExprs(std::move(rhs.multiplicativeExprs)),
          additiveOps(std::move(rhs.additiveOps)) {}

Variable MathExpr::calculate() const {
    auto itExpr = multiplicativeExprs.begin();
    Variable var = itExpr->get()->calculate();
    auto posIt = positions.begin();

    for (auto &&op : additiveOps) {
        var.setPosition(*posIt++);
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

void MathExpr::addPlus(exprPtr multiplicativeExpr, SignPosition position) {
    multiplicativeExprs.push_back(std::move(multiplicativeExpr));
    additiveOps.push_back(tkom::TokenType::Plus);
    addPosition(position);
}

void MathExpr::addMinus(exprPtr multiplicativeExpr, SignPosition position) {
    multiplicativeExprs.push_back(std::move(multiplicativeExpr));
    additiveOps.push_back(tkom::TokenType::Minus);
    addPosition(position);
}