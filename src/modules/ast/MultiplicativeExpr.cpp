#include "MultiplicativeExpr.hpp"
#include "exception/Exception.hpp"

using namespace tkom::ast;

MultiplicativeExpr::MultiplicativeExpr(exprPtr baseMathExpr) {
    baseMathExprs.push_back(std::move(baseMathExpr));
}

MultiplicativeExpr::MultiplicativeExpr(MultiplicativeExpr &&rhs) noexcept
        : baseMathExprs(std::move(rhs.baseMathExprs)),
          multiplicativeOps(std::move(rhs.multiplicativeOps)) {}

Variable MultiplicativeExpr::calculate() {
    auto itExpr = baseMathExprs.begin();
    Variable var = itExpr->get()->calculate();

    for (auto &&op : multiplicativeOps) {
        ++itExpr;
        if (op == tkom::TokenType::Multiply)
            var = var * itExpr->get()->calculate();
        else if (op == tkom::TokenType::Divide)
            var = var / itExpr->get()->calculate();
        else if (op == tkom::TokenType::Modulo)
            var = var % itExpr->get()->calculate();
        else
            throw Exception("Bad TokenType in multiplicativeOps");
    }

    return var;
}

void MultiplicativeExpr::addMultiply(exprPtr baseMathExpr) {
    baseMathExprs.push_back(std::move(baseMathExpr));
    multiplicativeOps.push_back(tkom::TokenType::Multiply);
}

void MultiplicativeExpr::addDivide(exprPtr baseMathExpr) {
    baseMathExprs.push_back(std::move(baseMathExpr));
    multiplicativeOps.push_back(tkom::TokenType::Divide);
}

void MultiplicativeExpr::addModulo(exprPtr baseMathExpr) {
    baseMathExprs.push_back(std::move(baseMathExpr));
    multiplicativeOps.push_back(tkom::TokenType::Modulo);
}