#include <catch.hpp>
#include "modules/ast/expression/LogicExpr.hpp"

using namespace tkom::ast;

SCENARIO("Test for LogicExpr", "[ast][expr][LogicExpr]") {
    GIVEN("LogicExpr object from Variable") {
        Variable variable;
        LogicExpr expr(std::make_unique<BaseMathExpr>(variable));

        Variable rhs;
        auto andExpr = std::make_unique<AndExpr>(std::make_unique<BaseMathExpr>(rhs));

        THEN("Calculate method return variable") {
            REQUIRE(expr.calculate() == variable);
        }

        WHEN("addOr method is coled") {
            THEN("Calculate method return true") {
                rhs = Variable({1, 2, 3});
                expr.addOr(std::move(andExpr));
                REQUIRE(expr.calculate());
            }
            THEN("Calculate method return false") {
                rhs = Variable();
                expr.addOr(std::move(andExpr));
                REQUIRE_FALSE(expr.calculate());
            }
        }
    }
}


