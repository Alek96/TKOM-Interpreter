#include <catch.hpp>
#include "modules/ast/FunctionDef.hpp"

#include <string>
#include <list>
#include "ast/statement/ReturnStatement.hpp"
#include "ast/expression/BaseMathExpr.hpp"

using namespace tkom::ast;

SCENARIO("Test for FunctionDef", "[ast][statement][FunctionDef]") {
    GIVEN("FunctionDef object") {
        std::string id = "id";
        FunctionDef functionDef(id);
        WHEN("Method getIdentifier is coled") {
            const std::string retId = functionDef.getIdentifier();
            THEN("Returned id is correct") {
                REQUIRE(retId == id);
            }
        }
        WHEN("Parameters is added") {
            std::string param = "param";
            functionDef.addParameter(param);
            THEN("Method exist return true") {
                REQUIRE(functionDef.getFunctionBlock().existVariable(param));
            }
            WHEN("Variable is added to functionBlock") {
                std::string varName = "variable";
                Variable var({1, 2, 3});
                functionDef.getFunctionBlock().addVariable(varName, Variable(var));
                THEN("Method exist return true") {
                    REQUIRE(functionDef.getFunctionBlock().existVariable(varName));
                }
            }
            WHEN("ReturnStatement is added to functionBlock") {
                Variable var({1, 2, 3});
                functionDef.getFunctionBlock().addInstruction(
                        std::make_unique<ReturnStatement>(std::make_unique<BaseMathExpr>(var)));
                THEN("run Method return all commend in block and return variable") {
                    std::list<Variable> params({var});
                    Return ret = functionDef.run(params);
                    REQUIRE(ret.type == Return::_variable);
                    REQUIRE(ret.variable == var);
                }
            }
            WHEN("ReturnStatement is added to functionBlock") {
                Variable var({1, 2, 3});
                Variable &funParam = functionDef.getFunctionBlock().findVariable(param);
                functionDef.getFunctionBlock().addInstruction(
                        std::make_unique<ReturnStatement>(std::make_unique<BaseMathExpr>(funParam)));
//                THEN("run Method return all commend in block and return variable parameter") {
//                    std::list<Variable> params({var});
//                    Return ret = functionDef.run(params);
//                    REQUIRE(ret.type == Return::_variable);
//                    REQUIRE(ret.variable == var);
//                }
            }
        }
    }
}

