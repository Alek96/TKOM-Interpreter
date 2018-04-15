#include <catch.hpp>
#include "ast/RelationalExpr.hpp"

using namespace tkom::ast;

SCENARIO("Test for RelationalExpr", "[ast][expr][RelationalExpr]") {
    GIVEN("RelationalExpr object from Variable") {
        Variable variable({1, 2, 3});
        RelationalExpr expr(std::make_unique<BaseMathExpr>(variable));

        Variable rhs;
        auto baseLogicExpr = std::make_unique<BaseLogicExpr>(std::make_unique<BaseMathExpr>(rhs));

        THEN("Calculate method return variable") {
            REQUIRE(expr.calculate() == variable);
        }

        WHEN("addEquality method is coled") {
            THEN("Calculate method return true") {
                rhs = Variable({1,2,3});
                expr.addEquality(std::move(baseLogicExpr));
                REQUIRE(expr.calculate());
            }
            THEN("Calculate method return false") {
                rhs = Variable({1,2,4});
                expr.addEquality(std::move(baseLogicExpr));
                REQUIRE_FALSE(expr.calculate());
            }
        }


        WHEN("addInequality method is coled") {
            THEN("Calculate method return true") {
                rhs = Variable({1,2,4});
                expr.addInequality(std::move(baseLogicExpr));
                REQUIRE(expr.calculate());
            }
            THEN("Calculate method return false") {
                rhs = Variable({1,2,3});
                expr.addInequality(std::move(baseLogicExpr));
                REQUIRE_FALSE(expr.calculate());
            }
        }

        WHEN("addLess method is coled") {
            THEN("Calculate method return true") {
                rhs = Variable({1,2,4});
                expr.addLess(std::move(baseLogicExpr));
                REQUIRE(expr.calculate());
            }
            THEN("Calculate method return false") {
                rhs = Variable({1,2,3});
                expr.addLess(std::move(baseLogicExpr));
                REQUIRE_FALSE(expr.calculate());
            }
        }

        WHEN("addGreater method is coled") {
            THEN("Calculate method return true") {
                rhs = Variable({1,2,2});
                expr.addGreater(std::move(baseLogicExpr));
                REQUIRE(expr.calculate());
            }
            THEN("Calculate method return false") {
                rhs = Variable({1,2,3});
                expr.addGreater(std::move(baseLogicExpr));
                REQUIRE_FALSE(expr.calculate());
            }
        }

        WHEN("addLessOrEqual method is coled") {
            THEN("Calculate method return true") {
                rhs = Variable({1,2,3});
                expr.addLessOrEqual(std::move(baseLogicExpr));
                REQUIRE(expr.calculate());
            }
            THEN("Calculate method return false") {
                rhs = Variable({1,2,2});
                expr.addLessOrEqual(std::move(baseLogicExpr));
                REQUIRE_FALSE(expr.calculate());
            }
        }

        WHEN("addGreaterOrEqual method is coled") {
            THEN("Calculate method return true") {
                rhs = Variable({1,2,3});
                expr.addGreaterOrEqual(std::move(baseLogicExpr));
                REQUIRE(expr.calculate());
            }
            THEN("Calculate method return false") {
                rhs = Variable({1,2,4});
                expr.addGreaterOrEqual(std::move(baseLogicExpr));
                REQUIRE_FALSE(expr.calculate());
            }
        }
    }
}
