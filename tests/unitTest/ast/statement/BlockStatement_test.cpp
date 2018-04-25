#include <catch.hpp>
#include "modules/ast/statement/BlockStatement.hpp"

#include <memory>
#include <string>
#include "ast/Variable.hpp"
#include "ast/expression/BaseMathExpr.hpp"
#include "ast/Return.hpp"
#include "ast/statement/ReturnStatement.hpp"
#include "ast/statement/AssignStatement.hpp"

using namespace tkom::ast;

SCENARIO("Test for BlockStatement", "[ast][statement][BlockStatement]") {
    GIVEN("BlockStatement object") {
        BlockStatement block;

        WHEN("Variable is added to block") {
            Variable var({1, 2, 3});
            std::string id = "variable";
            block.addVariable(id, Variable(var));
            THEN("Method exist can find it") {
                REQUIRE(block.existVariable(id));
            }
            THEN("We can modify it") {
                Variable modVar({3, 2, 1});
                block.findVariable(id) = modVar;
                REQUIRE(block.findVariable(id) == modVar);
            }
            THEN("Variable is erased from block") {
                block.eraseVariable(id);
                THEN("Method exist can't find it") {
                    REQUIRE_FALSE(block.existVariable(id));
                }
            }
            THEN("New block is created from  previous") {
                BlockStatement newBlock(&block);
                THEN("Method exist can find variable") {
                    REQUIRE(block.existVariable(id));
                }
                THEN("We can modify it") {
                    Variable modVar({3, 2, 1});
                    block.findVariable(id) = modVar;
                    REQUIRE(block.findVariable(id) == modVar);
                }
            }
        }
        WHEN("Instruction is added to block") {
            Variable var({1, 2, 3});
            auto statement = std::make_unique<ReturnStatement>(std::make_unique<BaseMathExpr>(var));
            block.addInstruction(std::move(statement));

            THEN("Method run will return Variable from ReturnStatement") {
                REQUIRE(block.run().variable == var);
            }
            THEN("Second BlockStatement object is created from previous block") {
                BlockStatement block2(&block);
                THEN("Method run will return Variable from ReturnStatement") {
                    REQUIRE(block.run().variable == var);
                }
            }
        }
        WHEN("3 instruction are added to block and second is ReturnStatement::_variable") {
            Variable var1({1, 1, 1});
            Variable var2({2, 2, 2});
            Variable var3({3, 3, 3});
            block.addInstruction(std::make_unique<AssignStatement>(var1, std::make_unique<BaseMathExpr>(var2)));
            block.addInstruction(std::make_unique<ReturnStatement>(std::make_unique<BaseMathExpr>(var1)));
            block.addInstruction(std::make_unique<AssignStatement>(var1, std::make_unique<BaseMathExpr>(var3)));

            THEN("Method run will run only the first two instructions") {
                Return ret = block.run();
                REQUIRE(var1 == var2);
                REQUIRE(ret.variable == var2);
                REQUIRE_FALSE(var1 == var3);
            }
        }
        WHEN("3 instruction are added to block and second is ReturnStatement::_break") {
            Variable var1({1, 1, 1});
            Variable var2({2, 2, 2});
            Variable var3({3, 3, 3});
            block.addInstruction(std::make_unique<AssignStatement>(var1, std::make_unique<BaseMathExpr>(var2)));
            block.addInstruction(std::make_unique<ReturnStatement>(Return::_break));
            block.addInstruction(std::make_unique<AssignStatement>(var1, std::make_unique<BaseMathExpr>(var3)));

            THEN("Method run will run only the first two instructions") {
                Return ret = block.run();
                REQUIRE(var1 == var2);
                REQUIRE(ret.type == Return::_break);
                REQUIRE_FALSE(var1 == var3);
            }
        }
        WHEN("3 instruction are added to block and second is ReturnStatement::_continue") {
            Variable var1({1, 1, 1});
            Variable var2({2, 2, 2});
            Variable var3({3, 3, 3});
            block.addInstruction(std::make_unique<AssignStatement>(var1, std::make_unique<BaseMathExpr>(var2)));
            block.addInstruction(std::make_unique<ReturnStatement>(Return::_continue));
            block.addInstruction(std::make_unique<AssignStatement>(var1, std::make_unique<BaseMathExpr>(var3)));

            THEN("Method run will run only the first two instructions") {
                Return ret = block.run();
                REQUIRE(var1 == var2);
                REQUIRE(ret.type == Return::_continue);
                REQUIRE_FALSE(var1 == var3);
            }
        }
        WHEN("3 instruction are added to block and second is ReturnStatement::_none") {
            Variable var1({1, 1, 1});
            Variable var2({2, 2, 2});
            Variable var3({3, 3, 3});
            block.addInstruction(std::make_unique<AssignStatement>(var1, std::make_unique<BaseMathExpr>(var2)));
            block.addInstruction(std::make_unique<ReturnStatement>(Return::_none));
            block.addInstruction(std::make_unique<AssignStatement>(var1, std::make_unique<BaseMathExpr>(var3)));

            THEN("Method run will run all three instructions") {
                Return ret = block.run();
                REQUIRE_FALSE(var1 == var2);
                REQUIRE(ret.type == Return::_none);
                REQUIRE(var1 == var3);
            }
        }
    }
}


