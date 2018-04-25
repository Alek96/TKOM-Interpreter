#include <catch.hpp>
#include "modules/ast/statement/FunctionCall.hpp"

#include <string>
#include <list>
#include "ast/statement/ReturnStatement.hpp"
#include "ast/expression/BaseMathExpr.hpp"

using namespace tkom::ast;

SCENARIO("Test for FunctionCall", "[ast][statement][FunctionCall]") {
    GIVEN("FunctionCall object without parameters") {
        std::string functionId = "id";
        FunctionDef functionDef(functionId);

        Variable var({1, 2, 3});
        functionDef.getFunctionBlock().addInstruction(
                std::make_unique<ReturnStatement>(std::make_unique<BaseMathExpr>(var)));

        FunctionCall functionCall(functionDef);

        WHEN("Method run is coled") {
           Return ret = functionCall.run();
           THEN("Called function is proceeded") {
               REQUIRE(ret.type == Return::_none);
               REQUIRE(ret.variable == var);
           }
        }
    }
    GIVEN("FunctionCall object with one parameter") {
        std::string functionId = "id";
        FunctionDef functionDef(functionId);

        std::string param = "param";
        functionDef.addParameter(param);

        Variable var({1, 2, 3});
        functionDef.getFunctionBlock().addInstruction(
                std::make_unique<ReturnStatement>(std::make_unique<BaseMathExpr>(var)));

        FunctionCall functionCall(functionDef);
        auto expr = std::make_unique<BaseMathExpr>(new Variable({1}));
        functionCall.addExpression(std::move(expr));

        WHEN("Method run is coled") {
            Return ret = functionCall.run();
            THEN("Called function is proceeded") {
                REQUIRE(ret.type == Return::_none);
                REQUIRE(ret.variable == var);
            }
        }
    }
}


