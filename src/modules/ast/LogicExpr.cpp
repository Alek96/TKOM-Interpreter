#include "LogicExpr.hpp"

using namespace tkom::ast;

LogicExpr::LogicExpr(AndExpr &&andExpr) {
    andExprs.push_back(std::move(andExpr));
}

LogicExpr::LogicExpr(LogicExpr &&rhs) noexcept
        : andExprs(std::move(rhs.andExprs)),
          orOps(std::move(rhs.orOps)) {}

Variable LogicExpr::calculate() {
    if (andExprs.empty()) {
        return Variable();
    }
    Variable var = andExprs[0].calculate();
    for (unsigned int i = 1; i < andExprs.size(); ++i) {
        if (orOps[i - 1] == tkom::TokenType::Or)
            var = var && andExprs[i].calculate();
    }
    return var;
}

void LogicExpr::addOr(AndExpr &&andExpr) {
    andExprs.push_back(std::move(andExpr));
    orOps.push_back(tkom::TokenType::Or);
}