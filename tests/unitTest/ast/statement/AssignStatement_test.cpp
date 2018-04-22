#include <catch.hpp>
#include "modules/ast/statement/AssignStatement.hpp"

#include <memory>
#include "ast/Variable.hpp"
#include "ast/expression/BaseMathExpr.hpp"

using namespace tkom::ast;
using namespace Catch::Matchers;

SCENARIO("Test for AssignStatement", "[ast][statement][AssignStatement]") {
    GIVEN("AssignStatement created from Variable var1 and Expression created from var2") {
        Variable var1, var2;
        AssignStatement assign(var1, std::make_unique<BaseMathExpr>(var2));

        WHEN("run method is coled") {
            var1 = Variable({1, 2, 3});
            var2 = Variable({3, 2, 1});
            assign.run();
            THEN("var1 change value to var2") {
                REQUIRE(var1 == var2);
            }
        }
    }

    GIVEN("AssignStatement created from Variable var1 with index 3 and Expression created from var2") {
        Variable var1, var2;
        unsigned int idx = 2;
        AssignStatement assign(var1, idx, std::make_unique<BaseMathExpr>(var2));

        WHEN("var1 is 3-dimensional and var2 is 1-dimensional") {
            var1 = Variable({1, 2, 3});
            var2 = Variable({1});
            assign.run();
            THEN("Run method is working") {
                REQUIRE(var1[idx] == var2[0]);
            }
        }
        WHEN("var1 is 3-dimensional and var2 is 2-dimensional") {
            var1 = Variable({1, 2, 3});
            var2 = Variable({1, 2});
            THEN("Run method coled and Exception appears") {
                REQUIRE_THROWS(assign.run());
            }
            THEN("Run method coled and Exception appears with position") {
                tkom::SignPosition sPos;
                sPos.lineNumber = 2;
                assign.setPosition(sPos);
                REQUIRE_THROWS_WITH(assign.run(), Contains(sPos.toString()));
            }
        }
        WHEN("var1 is 2-dimensional and var2 is 1-dimensional, but index is 2") {
            var1 = Variable({1, 2});
            var2 = Variable({1});
            THEN("Run method coled and Exception appears") {
                REQUIRE_THROWS(assign.run());
            }
            THEN("Run method coled and Exception appears with position") {
                tkom::SignPosition sPos;
                sPos.lineNumber = 2;
                assign.setPosition(sPos);
                REQUIRE_THROWS_WITH(assign.run(), Contains(sPos.toString()));
            }
        }
    }
}
