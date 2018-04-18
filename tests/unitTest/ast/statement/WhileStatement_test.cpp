#include <catch.hpp>
#include "modules/ast/statement/WhileStatement.hpp"

#include <memory>
#include "ast/Variable.hpp"
#include "ast/expression/BaseMathExpr.hpp"
#include "ast/Return.hpp"
#include "ast/statement/BlockStatement.hpp"
#include "ast/statement/AssignStatement.hpp"
#include "ast/statement/IfStatement.hpp"
#include "ast/statement/ReturnStatement.hpp"
#include "ast/expression/MathExpr.hpp"
#include "ast/expression/RelationalExpr.hpp"
#include "exception/Exception.hpp"

using namespace tkom::ast;

SCENARIO("Test for WhileStatement", "[ast][statement][WhileStatement]") {
    GIVEN("WhileStatement object") {
        /*
         * while(exprVar < newExprVar) {
         *  exprVar = exprVar + 1;
         * }
         * */
        Variable exprVar({1});
        Variable oldExprVar(exprVar);
        Variable newExprVar({10});

        // expr < 10
        auto whileExpr = std::make_unique<RelationalExpr>(std::make_unique<BaseMathExpr>(exprVar));
        whileExpr->addLess(std::make_unique<BaseMathExpr>(newExprVar));
        // {...}
        auto whileBlock = std::make_unique<BlockStatement>();
        // exprVar = exprVar + 1
        auto addExpr = std::make_unique<MathExpr>(std::make_unique<BaseMathExpr>(exprVar));
        addExpr->addPlus(std::make_unique<BaseMathExpr>(new Variable({1})));
        whileBlock->addInstruction(std::make_unique<AssignStatement>(exprVar, std::move(addExpr)));

        WhileStatement whileStatement(std::move(whileExpr), std::move(whileBlock));

        WHEN("Method run is coled") {
            Return ret;

            REQUIRE_NOTHROW(ret = whileStatement.run());
            THEN("exprVar is equal to newExprVar") {
                REQUIRE(ret.type == Return::_none);
                REQUIRE_FALSE(exprVar == oldExprVar);
                REQUIRE(exprVar == newExprVar);
            }
        }
    }

    GIVEN("WhileStatement object 2") {
        /*
         * while(trueExprVar) {
         *   exprVar = exprVar + 1;
         *   if( exprVar == newExprVar )
         *     break;
         * }
         * */
        Variable trueExprVar({1});
        Variable exprVar({1});
        Variable newExprVar({10});

        // trueExprVar
        auto whileExpr = std::make_unique<BaseMathExpr>(trueExprVar);
        // {...}
        auto whileBlock = std::make_unique<BlockStatement>();
        // exprVar = exprVar + 1
        auto addExpr = std::make_unique<MathExpr>(std::make_unique<BaseMathExpr>(exprVar));
        addExpr->addPlus(std::make_unique<BaseMathExpr>(new Variable({1})));
        whileBlock->addInstruction(std::make_unique<AssignStatement>(exprVar, std::move(addExpr)));
        // if: exprVar == newExprVar
        auto ifExpr = std::make_unique<RelationalExpr>(std::make_unique<BaseMathExpr>(exprVar));
        ifExpr->addEquality(std::make_unique<BaseMathExpr>(newExprVar));
        // if: { break; }
        auto ifBlock = std::make_unique<BlockStatement>();
        ifBlock->addInstruction(std::make_unique<ReturnStatement>(Return::_break));
        // if
        whileBlock->addInstruction(std::make_unique<IfStatement>(std::move(ifExpr), std::move(ifBlock)));

        WhileStatement whileStatement(std::move(whileExpr), std::move(whileBlock));

        WHEN("Method run is coled") {
            Return ret;
            REQUIRE_NOTHROW(ret = whileStatement.run());
            THEN("exprVar is equal to newExprVar") {
                REQUIRE(ret.type == Return::_none);
                REQUIRE(exprVar == newExprVar);
            }
        }
    }

    GIVEN("WhileStatement object 3") {
        /*
         * while(trueExprVar) {
         *   exprVar = exprVar + 1;
         *   if( exprVar == newExprVar )
         *     return retVar;
         * }
         * */
        Variable trueExprVar({1});
        Variable exprVar({1});
        Variable newExprVar({10});
        Variable retVar({20});

        // trueExprVar
        auto whileExpr = std::make_unique<BaseMathExpr>(trueExprVar);
        // {...}
        auto whileBlock = std::make_unique<BlockStatement>();
        // exprVar = exprVar + 1
        auto addExpr = std::make_unique<MathExpr>(std::make_unique<BaseMathExpr>(exprVar));
        addExpr->addPlus(std::make_unique<BaseMathExpr>(new Variable({1})));
        whileBlock->addInstruction(std::make_unique<AssignStatement>(exprVar, std::move(addExpr)));
        // if: exprVar == newExprVar
        auto ifExpr = std::make_unique<RelationalExpr>(std::make_unique<BaseMathExpr>(exprVar));
        ifExpr->addEquality(std::make_unique<BaseMathExpr>(newExprVar));
        // if: { return retVar; }
        auto ifBlock = std::make_unique<BlockStatement>();
        ifBlock->addInstruction(std::make_unique<ReturnStatement>(std::make_unique<BaseMathExpr>(retVar)));
        // if
        whileBlock->addInstruction(std::make_unique<IfStatement>(std::move(ifExpr), std::move(ifBlock)));

        WhileStatement whileStatement(std::move(whileExpr), std::move(whileBlock));

        WHEN("Method run is coled") {
            Return ret;
            REQUIRE_NOTHROW(ret = whileStatement.run());
            THEN("exprVar is equal to newExprVar") {
                REQUIRE(ret.type == Return::_variable);
                REQUIRE(ret.variable == retVar);
                REQUIRE(exprVar == newExprVar);
            }
        }
    }
    GIVEN("WhileStatement object 4") {
        /*
         * while(trueExprVar) {
         *   exprVar = exprVar + 1;
         *   if( exprVar == newExprVar )
         *     continue;
         *
         *   exprVar2 = exprVar2 + 1;
         *   if( exprVar == newNewExprVar )
         *     break;
         * }
         * */
        Variable trueExprVar({1});
        Variable exprVar({1});
        Variable newExprVar({10});
        Variable newNewExprVar({20});
        Variable exprVar2(exprVar);

        // trueExprVar
        auto whileExpr = std::make_unique<BaseMathExpr>(trueExprVar);
        // {...}
        auto whileBlock = std::make_unique<BlockStatement>();

        // exprVar = exprVar + 1
        auto addExpr = std::make_unique<MathExpr>(std::make_unique<BaseMathExpr>(exprVar));
        addExpr->addPlus(std::make_unique<BaseMathExpr>(new Variable({1})));
        whileBlock->addInstruction(std::make_unique<AssignStatement>(exprVar, std::move(addExpr)));

        // if: exprVar == newExprVar
        auto ifExpr = std::make_unique<RelationalExpr>(std::make_unique<BaseMathExpr>(exprVar));
        ifExpr->addEquality(std::make_unique<BaseMathExpr>(newExprVar));
        // if: { continue; }
        auto ifBlock = std::make_unique<BlockStatement>();
        ifBlock->addInstruction(std::make_unique<ReturnStatement>(Return::_continue));
        // if
        whileBlock->addInstruction(std::make_unique<IfStatement>(std::move(ifExpr), std::move(ifBlock)));

        // exprVar2 = exprVar2 + 1
        auto addExpr2 = std::make_unique<MathExpr>(std::make_unique<BaseMathExpr>(exprVar2));
        addExpr2->addPlus(std::make_unique<BaseMathExpr>(new Variable({1})));
        whileBlock->addInstruction(std::make_unique<AssignStatement>(exprVar2, std::move(addExpr2)));

        // if: exprVar == newNewExprVar
        auto ifExpr2 = std::make_unique<RelationalExpr>(std::make_unique<BaseMathExpr>(exprVar));
        ifExpr2->addEquality(std::make_unique<BaseMathExpr>(newNewExprVar));
        // if: { break; }
        auto ifBlock2 = std::make_unique<BlockStatement>();
        ifBlock2->addInstruction(std::make_unique<ReturnStatement>(Return::_break));
        // if
        whileBlock->addInstruction(std::make_unique<IfStatement>(std::move(ifExpr2), std::move(ifBlock2)));


        WhileStatement whileStatement(std::move(whileExpr), std::move(whileBlock));

        WHEN("Method run is coled") {
            Return ret;
            REQUIRE_NOTHROW(ret = whileStatement.run());
            THEN("exprVar is equal to newExprVar") {
                REQUIRE(ret.type == Return::_none);
                REQUIRE(exprVar == newNewExprVar);
                REQUIRE(exprVar2 == newNewExprVar - Variable({1}));
            }
        }
    }


    /*GIVEN("WhileStatement object 5 that throw exception ") {
        *//*
         * while(trueExprVar) {}
         * *//*
        Variable trueExprVar({1});

        // trueExprVar
        auto whileExpr = std::make_unique<BaseMathExpr>(trueExprVar);
        // {...}
        auto whileBlock = std::make_unique<BlockStatement>();
        // while
        WhileStatement whileStatement(std::move(whileExpr), std::move(whileBlock));

        WHEN("Method run is coled") {
            THEN("Exception appears") {
                REQUIRE_THROWS(whileStatement.run());
            }
        }
    }*/
}


