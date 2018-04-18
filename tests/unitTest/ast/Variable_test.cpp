#include <catch.hpp>
#include "ast/Variable.hpp"

#include <vector>
#include "exception/Exception.hpp"

using namespace tkom;
using namespace tkom::ast;

SCENARIO("Test for Variable", "[ast][Variable]") {
    GIVEN("Empty Variable object") {
        Variable var;
        THEN("Method size return 0") {
            REQUIRE(var.size() == 0);
        }
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
        Variable var({1});
        THEN("Method size return 1") {
            REQUIRE(var.size() == 1);
        }
        THEN("Operator == works") {
            REQUIRE(var == Variable({1}));
            REQUIRE_FALSE(var == Variable({0}));
        }
        THEN("Operator != works") {
            REQUIRE_FALSE(var != Variable({1}));
            REQUIRE(var != Variable({0}));
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
            REQUIRE(var == Variable({1}));
        }
        THEN("Operator -a works") {
            REQUIRE(-var == Variable({-1}));
        }
        WHEN("Second variable object id given") {
            Variable var2({2});
            THEN("Operator a + b works") {
                REQUIRE(var + var2 == Variable({3}));
            }
            THEN("Operator a - b works") {
                REQUIRE(var - var2 == Variable({-1}));
            }
            THEN("Operator a * b works") {
                REQUIRE(var * var2 == Variable({2}));
            }
            THEN("Operator a / b works") {
                REQUIRE(var / var2 == Variable({0}));
            }
            THEN("Operator a % b works") {
                REQUIRE(var % var2 == Variable({1}));
            }
            THEN("Operator a && b works") {
                REQUIRE((var && var2));
                REQUIRE_FALSE((var && Variable()));
                REQUIRE_FALSE((Variable() && Variable()));
            }
            THEN("Operator a || b works") {
                REQUIRE((var || var2));
                REQUIRE((var || Variable()));
                REQUIRE_FALSE((Variable() || Variable()));
            }
        }
    }
    GIVEN("Variable object with 2 dimension") {
        Variable var({1, 2});
        THEN("Method size return 2") {
            REQUIRE(var.size() == 2);
        }
        THEN("Operator == works") {
            REQUIRE(var == Variable({1, 2}));
            REQUIRE_FALSE(var == Variable({0, 2}));
            REQUIRE_FALSE(var == Variable({1, 0}));
        }
        THEN("Operator != works") {
            REQUIRE_FALSE(var != Variable({1, 2}));
            REQUIRE(var != Variable({0, 2}));
            REQUIRE(var != Variable({1, 0}));
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
            REQUIRE(var == Variable({1, 2}));
        }
        THEN("Operator -a works") {
            REQUIRE(-var == Variable({-1, -2}));
        }
        WHEN("Second variable object id given") {
            Variable var2({3, 4});
            THEN("Operator a + b works") {
                REQUIRE(var + var2 == Variable({4, 6}));
            }
            THEN("Operator a - b works") {
                REQUIRE(var - var2 == Variable({-2, -2}));
            }
            THEN("Operator a * b not works") {
                REQUIRE_THROWS_AS(var * var2, MathException);
            }
            THEN("Operator a / b not works") {
                REQUIRE_THROWS_AS(var / var2, MathException);
            }
            THEN("Operator a % b not works") {
                REQUIRE_THROWS_AS(var % var2, MathException);
            }
            THEN("Operator a && b works") {
                REQUIRE((var && var2));
            }
            THEN("Operator a || b works") {
                REQUIRE((var || var2));
            }
        }
    }
    GIVEN("2 Variable objects with 1 and 2 dimensions") {
        Variable var1({2});
        Variable var2({2, 3});

        WHEN("Compering them") {
            THEN("Operator == works") {
                REQUIRE_FALSE(var1 == var2);
                REQUIRE_FALSE(var2 == var1);
            }
            THEN("Operator != works") {
                REQUIRE(var1 != var2);
                REQUIRE(var2 != var1);
            }
            THEN("Operator a + b works") {
                REQUIRE_THROWS_AS(var1 + var2, MathException);
                REQUIRE_THROWS_AS(var2 + var1, MathException);
            }
            THEN("Operator a - b works") {
                REQUIRE_THROWS_AS(var1 - var2, MathException);
                REQUIRE_THROWS_AS(var2 - var1, MathException);
            }
            THEN("Operator (a,b) * c works") {
                REQUIRE(var1 * var2 == Variable({4, 6}));
            }
            AND_THEN("Operator c * (a,b) works") {
                REQUIRE(var2 * var1 == Variable({4, 6}));
            }
            THEN("Operator (a,b) / c not works") {
                REQUIRE_THROWS_AS(var1 / var2, MathException);
            }
            AND_THEN("Operator c / (a,b) works") {
                REQUIRE(var2 / var1 == Variable({1, 1}));
            }
            THEN("Operator a % b works") {
                REQUIRE_THROWS_AS(var1 % var2, MathException);
                REQUIRE(var2 % var1 == Variable({0, 1}));
            }
            THEN("Operator a && b works") {
                REQUIRE((var1 && var2));
                REQUIRE((var2 && var1));
            }
            THEN("Operator a || b works") {
                REQUIRE((var1 || var2));
                REQUIRE((var2 || var1));
            }
        }
    }
}
