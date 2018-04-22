#include <catch.hpp>
#include "modules/ast/expression/MathExpr.hpp"

using namespace tkom::ast;
using namespace Catch::Matchers;

SCENARIO("Test for MathExpr", "[ast][expr][MathExpr]") {
    GIVEN("MathExpr object from Variable") {
        Variable variable({1, 2, 3});
        MathExpr expr(std::make_unique<BaseMathExpr>(variable));

        Variable rhs({1, 2, 3});
        auto multiplicativeExpr = std::make_unique<MultiplicativeExpr>(std::make_unique<BaseMathExpr>(rhs));

        Variable rhsException({1, 2});
        auto multiplicativeExprExc = std::make_unique<MultiplicativeExpr>(std::make_unique<BaseMathExpr>(rhsException));
        tkom::SignPosition sPos;
        sPos.lineNumber = 2;

        THEN("Calculate method return variable") {
            REQUIRE(expr.calculate() == variable);
        }

        WHEN("addPlus method is coled") {
            expr.addPlus(std::move(multiplicativeExpr));
            THEN("Calculate method return multiply Variable") {
                REQUIRE(expr.calculate() == variable + rhs);
            }
        }
        WHEN("addPlus method is coled") {
            expr.addPlus(std::move(multiplicativeExprExc), sPos);
            THEN("Calculate method return exception") {
                REQUIRE_THROWS_WITH(expr.calculate(), Contains(sPos.toString()));
            }
        }

        WHEN("addMinus method is coled") {
            expr.addMinus(std::move(multiplicativeExpr));
            THEN("Calculate method return multiply Variable") {
                REQUIRE(expr.calculate() == variable - rhs);
            }
        }
        WHEN("addMinus method is coled") {
            expr.addMinus(std::move(multiplicativeExprExc), sPos);
            THEN("Calculate method return exception") {
                REQUIRE_THROWS_WITH(expr.calculate(), Contains(sPos.toString()));
            }
        }
    }
}