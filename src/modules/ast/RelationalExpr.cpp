#include "RelationalExpr.hpp"

using namespace tkom::ast;

RelationalExpr::RelationalExpr(BaseLogicExpr &&baseLogicExpr) {
    baseLogicExprs.push_back(std::move(baseLogicExpr));
}

RelationalExpr::RelationalExpr(RelationalExpr &&rhs) noexcept
        : baseLogicExprs(std::move(rhs.baseLogicExprs)),
          relationOps(std::move(rhs.relationOps)) {}

Variable RelationalExpr::calculate() {
    if (baseLogicExprs.empty()) {
        return Variable();
    }
    Variable var = baseLogicExprs[0].calculate();
    for (unsigned int i = 1; i < baseLogicExprs.size(); ++i) {
        if (relationOps[i - 1] == tkom::TokenType::Equality)
            var = var == baseLogicExprs[i].calculate();
        else if (relationOps[i - 1] == tkom::TokenType::Inequality)
            var = var != baseLogicExprs[i].calculate();
        else if (relationOps[i - 1] == tkom::TokenType::Less)
            var = var < baseLogicExprs[i].calculate();
        else if (relationOps[i - 1] == tkom::TokenType::Greater)
            var = var > baseLogicExprs[i].calculate();
        else if (relationOps[i - 1] == tkom::TokenType::LessOrEqual)
            var = var <= baseLogicExprs[i].calculate();
        else if (relationOps[i - 1] == tkom::TokenType::GreaterOrEqual)
            var = var >= baseLogicExprs[i].calculate();
    }
    return var;
}

void RelationalExpr::addEquality(BaseLogicExpr &&baseLogicExpr) {
    baseLogicExprs.push_back(std::move(baseLogicExpr));
    relationOps.push_back(tkom::TokenType::Equality);
}

void RelationalExpr::addInequality(BaseLogicExpr &&baseLogicExpr) {
    baseLogicExprs.push_back(std::move(baseLogicExpr));
    relationOps.push_back(tkom::TokenType::Inequality);
}

void RelationalExpr::addLess(BaseLogicExpr &&baseLogicExpr) {
    baseLogicExprs.push_back(std::move(baseLogicExpr));
    relationOps.push_back(tkom::TokenType::Less);
}

void RelationalExpr::addGreater(BaseLogicExpr &&baseLogicExpr) {
    baseLogicExprs.push_back(std::move(baseLogicExpr));
    relationOps.push_back(tkom::TokenType::Greater);
}

void RelationalExpr::addLessOrEqual(BaseLogicExpr &&baseLogicExpr) {
    baseLogicExprs.push_back(std::move(baseLogicExpr));
    relationOps.push_back(tkom::TokenType::LessOrEqual);
}

void RelationalExpr::addGreaterOrEqual(BaseLogicExpr &&baseLogicExpr) {
    baseLogicExprs.push_back(std::move(baseLogicExpr));
    relationOps.push_back(tkom::TokenType::GreaterOrEqual);
}