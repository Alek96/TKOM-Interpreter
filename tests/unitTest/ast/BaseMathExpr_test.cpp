#include <catch.hpp>
#include "ast/BaseMathExpr.hpp"
#include <vector>

using namespace tkom::ast;

SCENARIO("Test for BaseMathExpr","[ast][BaseMathExpr]") {
    GIVEN("a Literal object") {
        Variable literal(std::vector<int>({1,2,3}));
        WHEN("BaseMathExpr object is create from Literal") {
            BaseMathExpr exp(new Variable(literal));
            THEN("Calculate method return Literal") {
                REQUIRE(exp.calculate() == literal);
            }
        }
        WHEN("BaseMathExpr object is create from Literal with unaryMathOp") {
            BaseMathExpr exp(new Variable(literal), true);
            THEN("Calculate method return Literal") {
                REQUIRE(exp.calculate() == -literal);
            }
        }
    }
    GIVEN("a Variable object") {
        Variable variable(std::vector<int>({1,2,3}));
        WHEN("BaseMathExpr object is create from Literal") {
            BaseMathExpr exp(variable);
            THEN("Calculate method return Literal") {
                REQUIRE(exp.calculate() == variable);
            }
        }
        WHEN("BaseMathExpr object is create from Literal with unaryMathOp") {
            BaseMathExpr exp(variable, true);
            THEN("Calculate method return Literal") {
                REQUIRE(exp.calculate() == -variable);
            }
        }
    }
}
