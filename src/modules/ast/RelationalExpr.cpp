#include "RelationalExpr.hpp"
#include "exception/Exception.hpp"

using namespace tkom::ast;

RelationalExpr::RelationalExpr(exprPtr baseLogicExpr) {
    baseLogicExprs.push_back(std::move(baseLogicExpr));
}

RelationalExpr::RelationalExpr(RelationalExpr &&rhs) noexcept
        : baseLogicExprs(std::move(rhs.baseLogicExprs)),
          relationOps(std::move(rhs.relationOps)) {}

Variable RelationalExpr::calculate() {
    auto itExpr = baseLogicExprs.begin();
    Variable var = itExpr->get()->calculate();

    for (auto &&op : relationOps) {
        ++itExpr;
        if (op == tkom::TokenType::Equality)
            var = var == itExpr->get()->calculate();
        else if (op == tkom::TokenType::Inequality)
            var = var != itExpr->get()->calculate();
        else if (op == tkom::TokenType::Less)
            var = var < itExpr->get()->calculate();
        else if (op == tkom::TokenType::Greater)
            var = var > itExpr->get()->calculate();
        else if (op == tkom::TokenType::LessOrEqual)
            var = var <= itExpr->get()->calculate();
        else if (op == tkom::TokenType::GreaterOrEqual)
            var = var >= itExpr->get()->calculate();
        else
            throw Exception("Bad TokenType in relationOps");
    }

    return var;
}

void RelationalExpr::addEquality(exprPtr baseLogicExpr) {
    baseLogicExprs.push_back(std::move(baseLogicExpr));
    relationOps.push_back(tkom::TokenType::Equality);
}

void RelationalExpr::addInequality(exprPtr baseLogicExpr) {
    baseLogicExprs.push_back(std::move(baseLogicExpr));
    relationOps.push_back(tkom::TokenType::Inequality);
}

void RelationalExpr::addLess(exprPtr baseLogicExpr) {
    baseLogicExprs.push_back(std::move(baseLogicExpr));
    relationOps.push_back(tkom::TokenType::Less);
}

void RelationalExpr::addGreater(exprPtr baseLogicExpr) {
    baseLogicExprs.push_back(std::move(baseLogicExpr));
    relationOps.push_back(tkom::TokenType::Greater);
}

void RelationalExpr::addLessOrEqual(exprPtr baseLogicExpr) {
    baseLogicExprs.push_back(std::move(baseLogicExpr));
    relationOps.push_back(tkom::TokenType::LessOrEqual);
}

void RelationalExpr::addGreaterOrEqual(exprPtr baseLogicExpr) {
    baseLogicExprs.push_back(std::move(baseLogicExpr));
    relationOps.push_back(tkom::TokenType::GreaterOrEqual);
}