#include <catch.hpp>
#include "modules/ast/statement/PrintStatement.hpp"

#include <memory>
#include <sstream>
#include <iostream>
#include "ast/Variable.hpp"
#include "ast/expression/BaseMathExpr.hpp"
#include "ast/Return.hpp"
#include "printer/Printer.hpp"

using namespace tkom::ast;

struct setPrinter {
    explicit setPrinter(std::stringstream& ss) {
        tkom::Printer::instance().setOutputStream(&ss);
        tkom::Printer::instance().setEnableOutput(true);
    }
    ~setPrinter() {
        tkom::Printer::instance().setOutputStream(&(std::cout));
        tkom::Printer::instance().setEnableOutput(false);
    }
};

SCENARIO("Test for PrintStatement", "[ast][statement][PrintStatement]") {
    GIVEN("PrintStatement object") {
        PrintStatement printStatement;
        std::stringstream ss;
        setPrinter setPrinter1(ss);

        WHEN("Expression is added") {
            Variable var({1,2,3});
            printStatement.addExpression(std::make_unique<BaseMathExpr>(var));
            THEN("Method run print variable") {
                REQUIRE(printStatement.run().type == Return::_none);
                REQUIRE(ss.str().find(var.toString()) != std::string::npos);
            }
            WHEN("Expression is added") {
                Variable var2({1,2,3});
                printStatement.addExpression(std::make_unique<BaseMathExpr>(var2));
                THEN("Method run print variable 1 and 2") {
                    REQUIRE(printStatement.run().type == Return::_none);
                    REQUIRE(ss.str().find(var.toString()) != std::string::npos);
                    REQUIRE(ss.str().find(var2.toString()) != std::string::npos);
                }
            }
            WHEN("String is added") {
                std::string message = "message";
                printStatement.addString(message);
                THEN("Method run print variable and message") {
                    REQUIRE(printStatement.run().type == Return::_none);
                    REQUIRE(ss.str().find(var.toString()) != std::string::npos);
                    REQUIRE(ss.str().find(message) != std::string::npos);
                }
            }
        }

        WHEN("String is added") {
            std::string message = "message";
            printStatement.addString(message);
            THEN("Method run print message") {
                REQUIRE(printStatement.run().type == Return::_none);
                REQUIRE(ss.str().find(message) != std::string::npos);
            }
            WHEN("Expression is added") {
                Variable var({1,2,3});
                printStatement.addExpression(std::make_unique<BaseMathExpr>(var));
                THEN("Method run print message and variable") {
                    REQUIRE(printStatement.run().type == Return::_none);
                    REQUIRE(ss.str().find(message) != std::string::npos);
                    REQUIRE(ss.str().find(var.toString()) != std::string::npos);
                }
            }
            WHEN("String is added") {
                std::string message2 = "message";
                printStatement.addString(message2);
                THEN("Method run print message 1 and 2") {
                    REQUIRE(printStatement.run().type == Return::_none);
                    REQUIRE(ss.str().find(message) != std::string::npos);
                    REQUIRE(ss.str().find(message2) != std::string::npos);
                }
            }
        }
    }
}

