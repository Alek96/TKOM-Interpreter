#include <catch.hpp>
#include "ast/BaseMathExpr.hpp"

using namespace tkom::ast;

SCENARIO("Test for BaseMathExpr", "[ast][expr][BaseMathExpr]") {
    GIVEN("a Literal object") {
        Variable literal({1, 2, 3});
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
        Variable variable({1, 2, 3});
        WHEN("BaseMathExpr object is create from Variable") {
            BaseMathExpr exp(variable);
            THEN("Calculate method return Literal") {
                REQUIRE(exp.calculate() == variable);
            }
        }
        WHEN("BaseMathExpr object is create from Variable with unaryMathOp") {
            BaseMathExpr exp(variable, true);
            THEN("Calculate method return Literal") {
                REQUIRE(exp.calculate() == -variable);
            }
        }
    }
    GIVEN("a LogicExpr object") {
        Variable variable({1, 2, 3});
        auto logicExpr = std::make_unique<BaseMathExpr>(variable);
        
        WHEN("BaseMathExpr object is create from LogicExpr") {
            BaseMathExpr exp(std::move(logicExpr));
            THEN("Calculate method return Literal") {
                REQUIRE(exp.calculate() == variable);
            }
        }
        WHEN("BaseMathExpr object is create from LogicExpr with unaryMathOp") {
            BaseMathExpr exp(std::move(logicExpr), true);
            THEN("Calculate method return Literal") {
                REQUIRE(exp.calculate() == -variable);
            }
        }
    }
}
