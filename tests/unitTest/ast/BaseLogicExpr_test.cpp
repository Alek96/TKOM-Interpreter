#include <catch.hpp>
#include "ast/BaseLogicExpr.hpp"

using namespace tkom::ast;

SCENARIO("Test for BaseLogicExpr", "[ast][expr][BaseLogicExpr]") {
    GIVEN("a MathExpr object") {
        Variable variable({1, 2, 3});
        auto mathExpr = std::make_unique<MathExpr>(std::make_unique<BaseMathExpr>(variable));

        WHEN("BaseLogicExpr object is create from MathExpr") {
            BaseLogicExpr exp(std::move(mathExpr));
            THEN("Calculate method return variable") {
                REQUIRE(exp.calculate() == variable);
            }
        }
        WHEN("BaseMathExpr object is create from MathExpr with unaryLogicOp") {
            BaseLogicExpr exp(std::move(mathExpr), true);
            THEN("Calculate method return negative Variable") {
                REQUIRE(exp.calculate() == !variable);
            }
        }
    }
}
