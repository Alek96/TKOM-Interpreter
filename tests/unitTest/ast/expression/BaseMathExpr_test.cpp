#include <catch.hpp>
#include "modules/ast/expression/BaseMathExpr.hpp"

#include <iostream>
#include "ast/statement/FunctionCall.hpp"
#include "ast/statement/ReturnStatement.hpp"

using namespace tkom::ast;
using namespace Catch::Matchers;

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
            THEN("Calculate method return Variable") {
                REQUIRE(exp.calculate() == variable);
            }
        }
        WHEN("BaseMathExpr object is create from Variable with unaryMathOp") {
            BaseMathExpr exp(variable, true);
            THEN("Calculate method return Variable") {
                REQUIRE(exp.calculate() == -variable);
            }
        }
    }
    GIVEN("a Variable object with index") {
        Variable variable({1, 2, 3});
        unsigned int index = 2;
        WHEN("BaseMathExpr object is create from Variable") {
            BaseMathExpr exp(variable, index);
            THEN("Calculate method return Variable[index]") {
                REQUIRE(exp.calculate()[0] == variable[index]);
            }
        }
        WHEN("BaseMathExpr object is create from Variable with unaryMathOp") {
            BaseMathExpr exp(variable, index, true);
            THEN("Calculate method return Variable[index]") {
                REQUIRE(exp.calculate()[0] == -variable[index]);
            }
        }

        WHEN("BaseMathExpr object is create from Variable (exception)") {
            tkom::SignPosition sPos;
            sPos.lineNumber = 2;
            index = 3;
            BaseMathExpr exp(variable, index);
            exp.addPosition(sPos);
            THEN("Calculate method return exception") {
                REQUIRE_THROWS_WITH(exp.calculate(), Contains(sPos.toString()));
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
    GIVEN("FunctionCall object") {
        std::string functionId = "id";
        FunctionDef functionDef(functionId);

        Variable var({1, 2, 3});
        functionDef.getFunctionBlock().addInstruction(
                std::make_unique<ReturnStatement>(std::make_unique<BaseMathExpr>(var)));

        auto functionCall = std::make_unique<FunctionCall>(functionDef);

        WHEN("BaseMathExpr object is create from FunctionCall") {
            BaseMathExpr exp(std::move(functionCall));
            THEN("Calculate method return Literal") {
                REQUIRE(exp.calculate() == var);
            }
        }
        WHEN("BaseMathExpr object is create from FunctionCall with unaryMathOp") {
            BaseMathExpr exp(std::move(functionCall), true);
            THEN("Calculate method return Literal") {
                REQUIRE(exp.calculate() == -var);
            }
        }
    }
}
