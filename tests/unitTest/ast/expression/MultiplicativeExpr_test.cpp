#include <catch.hpp>
#include "modules/ast/expression/MultiplicativeExpr.hpp"

using namespace tkom::ast;

SCENARIO("Test for MultiplicativeExpr", "[ast][expr][MultiplicativeExpr]") {
    GIVEN("MultiplicativeExpr object from Variable") {
        Variable variable({1, 2, 3});
        MultiplicativeExpr expr(std::make_unique<BaseMathExpr>(variable));

        THEN("Calculate method return variable") {
            REQUIRE(expr.calculate() == variable);
        }

        Variable rhs({2});

        WHEN("addMultiply method is coled") {
            expr.addMultiply(std::make_unique<BaseMathExpr>(rhs));
            THEN("Calculate method return multiply Variable") {
                REQUIRE(expr.calculate() == variable * rhs);
            }
        }
        WHEN("addDivide method is coled") {
            expr.addDivide(std::make_unique<BaseMathExpr>(rhs));
            THEN("Calculate method return multiply Variable") {
                REQUIRE(expr.calculate() == variable / rhs);
            }
        }
        WHEN("addModulo method is coled") {
            expr.addModulo(std::make_unique<BaseMathExpr>(rhs));
            THEN("Calculate method return multiply Variable") {
                REQUIRE(expr.calculate() == variable % rhs);
            }
        }
    }
}