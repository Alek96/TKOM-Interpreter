#include <catch.hpp>
#include "modules/ast/statement/ReturnStatement.hpp"

#include <memory>
#include "ast/Variable.hpp"
#include "ast/expression/BaseMathExpr.hpp"
#include "ast/Return.hpp"

using namespace tkom::ast;

SCENARIO("Test for ReturnStatement", "[ast][statement][ReturnStatement]") {
    GIVEN("ReturnStatement created from expression") {
        Variable var({1,2,3});
        ReturnStatement returnStatement(std::make_unique<BaseMathExpr>(var));

        WHEN("run method is coled") {
            Return ret = returnStatement.run();
            THEN("Variable from expression is returned") {
                REQUIRE(ret.type == Return::_variable);
                REQUIRE(ret.variable == var);
            }
        }
    }
    GIVEN("ReturnStatement created from type _break") {
        ReturnStatement returnStatement(Return::_break);

        WHEN("run method is coled") {
            Return ret = returnStatement.run();
            THEN("Variable from expression is returned") {
                REQUIRE(ret.type == Return::_break);
            }
        }
    }
    GIVEN("ReturnStatement created from type _continue") {
        ReturnStatement returnStatement(Return::_continue);

        WHEN("run method is coled") {
            Return ret = returnStatement.run();
            THEN("Variable from expression is returned") {
                REQUIRE(ret.type == Return::_continue);
            }
        }
    }
}
