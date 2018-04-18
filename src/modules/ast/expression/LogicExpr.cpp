#include "LogicExpr.hpp"

using namespace tkom::ast;

LogicExpr::LogicExpr(exprPtr andExpr) {
    andExprs.push_back(std::move(andExpr));
}

LogicExpr::LogicExpr(LogicExpr &&rhs) noexcept
        : andExprs(std::move(rhs.andExprs)) {}

Variable LogicExpr::calculate() const {
    Variable var = andExprs.begin()->get()->calculate();

    for(auto it = ++andExprs.begin(); it!=andExprs.end(); ++it) {
        var = var || it->get()->calculate();
        if (var)
            break;
    }

    return var;
}

void LogicExpr::addOr(exprPtr andExpr) {
    andExprs.push_back(std::move(andExpr));
}