#include "AndExpr.hpp"

#include "Variable.hpp"

using namespace tkom::ast;

AndExpr::AndExpr(RelationalExpr &&relationalExpr) {
    relationalExprs.push_back(std::move(relationalExpr));
}

AndExpr::AndExpr(AndExpr &&rhs) noexcept
        : relationalExprs(std::move(rhs.relationalExprs)) {}

Variable AndExpr::calculate() {
    Variable var({1});
    for (auto &&relationalExpr : relationalExprs) {
        var = var && relationalExpr.calculate();
    }

    return var;
}

void AndExpr::addAnd(RelationalExpr &&relationalExpr) {
    relationalExprs.push_back(std::move(relationalExpr));
}