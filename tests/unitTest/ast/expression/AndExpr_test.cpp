#include <catch.hpp>
#include "modules/ast/expression/AndExpr.hpp"

using namespace tkom::ast;

SCENARIO("Test for AndExpr", "[ast][expr][AndExpr]") {
    GIVEN("AndExpr object from Variable") {
        Variable variable({1, 2, 3});
        AndExpr expr(std::make_unique<BaseMathExpr>(variable));

        Variable rhs;
        auto relationalExpr = std::make_unique<RelationalExpr>(std::make_unique<BaseMathExpr>(rhs));

        THEN("Calculate method return variable") {
            REQUIRE(expr.calculate() == variable);
        }

        WHEN("addAnd method is coled") {
            THEN("Calculate method return true") {
                rhs = Variable({1, 2, 3});
                expr.addAnd(std::move(relationalExpr));
                REQUIRE(expr.calculate());
            }
            THEN("Calculate method return false") {
                rhs = Variable();
                expr.addAnd(std::move(relationalExpr));
                REQUIRE_FALSE(expr.calculate());
            }
        }
    }
}

