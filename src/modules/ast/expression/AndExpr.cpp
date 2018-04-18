#include "AndExpr.hpp"

#include "modules/ast/Variable.hpp"

using namespace tkom::ast;

AndExpr::AndExpr(exprPtr relationalExpr) {
    relationalExprs.push_back(std::move(relationalExpr));
}

AndExpr::AndExpr(AndExpr &&rhs) noexcept
        : relationalExprs(std::move(rhs.relationalExprs)) {}

Variable AndExpr::calculate() const {
    Variable var = relationalExprs.begin()->get()->calculate();

    for(auto it = ++relationalExprs.begin(); it!=relationalExprs.end(); ++it) {
        var = var && it->get()->calculate();
        if (!var)
            break;
    }

    return var;
}

void AndExpr::addAnd(exprPtr relationalExpr) {
    relationalExprs.push_back(std::move(relationalExpr));
}