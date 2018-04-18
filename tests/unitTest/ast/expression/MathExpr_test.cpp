#include <catch.hpp>
#include "modules/ast/expression/MathExpr.hpp"

using namespace tkom::ast;

SCENARIO("Test for MathExpr", "[ast][expr][MathExpr]") {
    GIVEN("MathExpr object from Variable") {
        Variable variable({1, 2, 3});
        MathExpr expr(std::make_unique<BaseMathExpr>(variable));

        Variable rhs({1, 2, 3});
        auto multiplicativeExpr = std::make_unique<MultiplicativeExpr>(std::make_unique<BaseMathExpr>(rhs));

        THEN("Calculate method return variable") {
            REQUIRE(expr.calculate() == variable);
        }

        WHEN("addPlus method is coled") {
            expr.addPlus(std::move(multiplicativeExpr));
            THEN("Calculate method return multiply Variable") {
                REQUIRE(expr.calculate() == variable + rhs);
            }
        }
        WHEN("addMinus method is coled") {
            expr.addMinus(std::move(multiplicativeExpr));
            THEN("Calculate method return multiply Variable") {
                REQUIRE(expr.calculate() == variable - rhs);
            }
        }
    }
}