#include <catch.hpp>
#include "ast/Variable.hpp"

#include <vector>

using namespace tkom;
using namespace tkom::ast;

SCENARIO("Test for Variable", "[ast][Variable]") {
    GIVEN("Empty Variable object") {
        Variable var;
        THEN("Operator == works") {
            REQUIRE(var == Variable());
        }
        THEN("Operator != works") {
            REQUIRE_FALSE(var != Variable());
        }
        THEN("Operator * works") {
            REQUIRE((*var).empty());
        }
        THEN("Operator bool works") {
            REQUIRE_FALSE(var);
        }
        THEN("Operator !a works") {
            REQUIRE(!var);
        }
    }
    GIVEN("Variable object with 1 dimension") {
        Variable var(std::vector<int>({1}));
        THEN("Operator == works") {
            REQUIRE(var == Variable(std::vector<int>({1})));
            REQUIRE_FALSE(var == Variable(std::vector<int>({0})));
        }
        THEN("Operator != works") {
            REQUIRE_FALSE(var != Variable(std::vector<int>({1})));
            REQUIRE(var != Variable(std::vector<int>({0})));
        }
        WHEN("Create new object be move") {
            Variable var3(var);
            Variable var2(std::move(var));
            THEN("Move operation was correct") {
                REQUIRE(var == Variable());
                REQUIRE(var2 == var3);
            }
        }
        THEN("Operator * works") {
            REQUIRE(*var == std::vector<int>({1}));
        }
        THEN("Operator [] works") {
            REQUIRE(var[0] == 1);
        }
        THEN("Operator bool works") {
            REQUIRE(var);
        }
        THEN("Operator !a works") {
            REQUIRE_FALSE(!var);
        }
        THEN("Operator +a works") {
            REQUIRE(var == Variable(std::vector<int>({1})));
        }
        THEN("Operator -a works") {
            REQUIRE(-var == Variable(std::vector<int>({-1})));
        }
        WHEN("Second variable object id given") {
            Variable var2(std::vector<int>({2}));
            THEN("Operator a + b works") {
                REQUIRE(var + var2 == Variable(std::vector<int>({3})));
            }
            THEN("Operator a - b works") {
                REQUIRE(var - var2 == Variable(std::vector<int>({-1})));
            }
            THEN("Operator a * b works") {
                REQUIRE(var * var2 == Variable(std::vector<int>({2})));
            }
            THEN("Operator a / b works") {
                REQUIRE(var / var2 == Variable(std::vector<int>({0})));
            }
            THEN("Operator a % b works") {
                REQUIRE(var % var2 == Variable(std::vector<int>({1})));
            }
            THEN("Operator a && b works") {
                REQUIRE((var && var2));
                REQUIRE((var && Variable(std::vector<int>({1}))));
                REQUIRE_FALSE((var && Variable(std::vector<int>({0}))));
                REQUIRE_FALSE((Variable(std::vector<int>({0})) && Variable(std::vector<int>({0}))));
            }
            THEN("Operator a || b works") {
                REQUIRE((var || var2));
                REQUIRE((var || Variable(std::vector<int>({1}))));
                REQUIRE((var || Variable(std::vector<int>({0}))));
                REQUIRE_FALSE((Variable(std::vector<int>({0})) || Variable(std::vector<int>({0}))));
            }
        }
    }
    GIVEN("Variable object with 2 dimension") {
        Variable var(std::vector<int>({1, 2}));
        THEN("Operator == works") {
            REQUIRE(var == Variable(std::vector<int>({1,2})));
            REQUIRE_FALSE(var == Variable(std::vector<int>({0,2})));
            REQUIRE_FALSE(var == Variable(std::vector<int>({1,0})));
        }
        THEN("Operator != works") {
            REQUIRE_FALSE(var != Variable(std::vector<int>({1,2})));
            REQUIRE(var != Variable(std::vector<int>({0,2})));
            REQUIRE(var != Variable(std::vector<int>({1,0})));
        }
        WHEN("Create new object be move") {
            Variable var3(var);
            Variable var2(std::move(var));
            THEN("Move operation was correct") {
                REQUIRE(var == Variable());
                REQUIRE(var2 == var3);
            }
        }
        THEN("Operator * works") {
            REQUIRE(*var == std::vector<int>({1, 2}));
        }
        THEN("Operator [] works") {
            REQUIRE(var[0] == 1);
            REQUIRE(var[1] == 2);
        }
        THEN("Operator bool works") {
            REQUIRE(var);
        }
        THEN("Operator !a works") {
            REQUIRE_FALSE(!var);
        }
        THEN("Operator +a works") {
            REQUIRE(var == Variable(std::vector<int>({1, 2})));
        }
        THEN("Operator -a works") {
            REQUIRE(-var == Variable(std::vector<int>({-1, -2})));
        }
        WHEN("Second variable object id given") {
            Variable var2(std::vector<int>({3, 4}));
            THEN("Operator a + b works") {
                REQUIRE(var + var2 == Variable(std::vector<int>({4, 6})));
            }
            THEN("Operator a - b works") {
                REQUIRE(var - var2 == Variable(std::vector<int>({-2, -2})));
            }
            THEN("Operator a * b works") {
                REQUIRE(var * var2 == Variable(std::vector<int>({3, 8})));
            }
            THEN("Operator a / b works") {
                REQUIRE(var / var2 == Variable(std::vector<int>({0, 0})));
            }
            THEN("Operator a % b works") {
                REQUIRE(var % var2 == Variable(std::vector<int>({1, 2})));
            }
            THEN("Operator a && b works") {
                REQUIRE((var && var2));
                REQUIRE_FALSE((var && Variable(std::vector<int>({0, 0}))));
                REQUIRE_FALSE((Variable(std::vector<int>({0, 0})) && Variable(std::vector<int>({0, 0}))));
            }
            THEN("Operator a || b works") {
                REQUIRE((var || var2));
                REQUIRE((var || Variable(std::vector<int>({0, 0}))));
                REQUIRE_FALSE((Variable(std::vector<int>({0, 0})) || Variable(std::vector<int>({0, 0}))));
            }
        }
    }
    GIVEN("2 Variable objects with 1 and 2 dimensions") {
        Variable var1(std::vector<int>({1}));
        Variable var2(std::vector<int>({2, 3}));

        WHEN("Compering them") {
            THEN("Operator == works") {
                REQUIRE_FALSE(var1 == var2);
            }
            THEN("Operator != works") {
                REQUIRE(var1 != var2);
            }
            THEN("Operator a + b works") {
                REQUIRE_FALSE(var1 + var2);
            }
            THEN("Operator a - b works") {
                REQUIRE_FALSE(var1 - var2);
            }
            THEN("Operator a * b works") {
                REQUIRE_FALSE(var1 * var2);
            }
            THEN("Operator a / b works") {
                REQUIRE_FALSE(var1 / var2);
            }
            THEN("Operator a % b works") {
                REQUIRE_FALSE(var1 % var2);
            }
            THEN("Operator a && b works") {
                REQUIRE((var1 && var2));
            }
            THEN("Operator a || b works") {
                REQUIRE((var1 || var2));
            }
        }
    }
}
