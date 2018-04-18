#include <catch.hpp>
#include "modules/ast/statement/IfStatement.hpp"

#include <memory>
#include "ast/Variable.hpp"
#include "ast/expression/BaseMathExpr.hpp"
#include "ast/Return.hpp"
#include "ast/statement/BlockStatement.hpp"
#include "ast/statement/ReturnStatement.hpp"

using namespace tkom::ast;

SCENARIO("Test for IfStatement", "[ast][statement][IfStatement]") {
    GIVEN("IfStatement object with ifBlock and true expression") {
        Variable exprVar({1});
        Variable ifVar({2});

        auto ifBlok = std::make_unique<BlockStatement>();
        ifBlok->addInstruction(std::make_unique<ReturnStatement>(std::make_unique<BaseMathExpr>(ifVar)));

        IfStatement ifStatement(std::make_unique<BaseMathExpr>(exprVar), std::move(ifBlok));

        WHEN("Method run is coled") {
            Return ret = ifStatement.run();
            THEN("The method run ifBlock") {
                REQUIRE(ret.variable == ifVar);
            }
        }
    }

    GIVEN("IfStatement object with ifBlock and false expression") {
        Variable exprVar;
        Variable ifVar({2});

        auto ifBlok = std::make_unique<BlockStatement>();
        ifBlok->addInstruction(std::make_unique<ReturnStatement>(std::make_unique<BaseMathExpr>(ifVar)));

        IfStatement ifStatement(std::make_unique<BaseMathExpr>(exprVar), std::move(ifBlok));

        WHEN("Method run is coled") {
            Return ret = ifStatement.run();
            THEN("The method run ifBlock") {
                REQUIRE(ret.type == Return::_none);
            }
        }
    }

    GIVEN("IfStatement object with ifBlock, elseBlock and true expression") {
        Variable exprVar({1});
        Variable ifVar({2});
        Variable elseVar({2});

        auto ifBlok = std::make_unique<BlockStatement>();
        ifBlok->addInstruction(std::make_unique<ReturnStatement>(std::make_unique<BaseMathExpr>(ifVar)));

        auto elseBlok = std::make_unique<BlockStatement>();
        elseBlok->addInstruction(std::make_unique<ReturnStatement>(std::make_unique<BaseMathExpr>(elseVar)));

        IfStatement ifStatement(std::make_unique<BaseMathExpr>(exprVar), std::move(ifBlok), std::move(elseBlok));

        WHEN("Method run is coled") {
            Return ret = ifStatement.run();
            THEN("The method run ifBlock") {
                REQUIRE(ret.variable == ifVar);
            }
        }
    }

    GIVEN("IfStatement object with ifBlock, elseBlock and false expression") {
        Variable exprVar;
        Variable ifVar({2});
        Variable elseVar({2});

        auto ifBlok = std::make_unique<BlockStatement>();
        ifBlok->addInstruction(std::make_unique<ReturnStatement>(std::make_unique<BaseMathExpr>(ifVar)));

        auto elseBlok = std::make_unique<BlockStatement>();
        elseBlok->addInstruction(std::make_unique<ReturnStatement>(std::make_unique<BaseMathExpr>(elseVar)));

        IfStatement ifStatement(std::make_unique<BaseMathExpr>(exprVar), std::move(ifBlok), std::move(elseBlok));

        WHEN("Method run is coled") {
            Return ret = ifStatement.run();
            THEN("The method run ifBlock") {
                REQUIRE(ret.variable == elseVar);
            }
        }
    }
}


