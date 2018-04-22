#include "MultiplicativeExpr.hpp"
#include "exception/Exception.hpp"

using namespace tkom;
using namespace tkom::ast;

MultiplicativeExpr::MultiplicativeExpr(exprPtr baseMathExpr) {
    baseMathExprs.push_back(std::move(baseMathExpr));
}

MultiplicativeExpr::MultiplicativeExpr(MultiplicativeExpr &&rhs) noexcept
        : baseMathExprs(std::move(rhs.baseMathExprs)),
          multiplicativeOps(std::move(rhs.multiplicativeOps)) {}

Variable MultiplicativeExpr::calculate() const {
    auto itExpr = baseMathExprs.begin();
    Variable var = itExpr->get()->calculate();
    auto posIt = positions.begin();

    for (auto &&op : multiplicativeOps) {
        var.setPosition(*posIt++);

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

void MultiplicativeExpr::addMultiply(exprPtr baseMathExpr, SignPosition position) {
    baseMathExprs.push_back(std::move(baseMathExpr));
    multiplicativeOps.push_back(tkom::TokenType::Multiply);
    addPosition(position);
}

void MultiplicativeExpr::addDivide(exprPtr baseMathExpr, SignPosition position) {
    baseMathExprs.push_back(std::move(baseMathExpr));
    multiplicativeOps.push_back(tkom::TokenType::Divide);
    addPosition(position);
}

void MultiplicativeExpr::addModulo(exprPtr baseMathExpr, SignPosition position) {
    baseMathExprs.push_back(std::move(baseMathExpr));
    multiplicativeOps.push_back(tkom::TokenType::Modulo);
    addPosition(position);
}