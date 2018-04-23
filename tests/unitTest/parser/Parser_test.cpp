#include <catch.hpp>
#include "parser/Parser.hpp"

#include <iostream>
#include <memory>
#include <sstream>
#include "token/TokenType.hpp"
#include "token/Token.hpp"

#include <functional>
#include <modules/printer/Printer.hpp>

using namespace tkom;
using namespace tkom::ast;
using namespace Catch::Matchers;

void printException(const std::function<void()> &func) {
    try {
        func();
    } catch (Exception &e) {
        std::cout << e.what() << "\n";
    }
}

struct setParser {
    explicit setParser(std::string ss)
            : streamValue(std::move(ss)), stream(streamValue), parser(std::make_unique<Lexer>(stream)) {
    }

    Parser &getParser() {
        return parser;
    }

private:
    std::string streamValue;
    std::stringstream stream;
    Parser parser;
};

SCENARIO("Function definition", "[Parser]") {
    std::string streamValue = " ";
    std::stringstream stream(streamValue);
    std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(stream);
    Parser parser(std::move(lexer));

    WHEN("Wrong function definition") {
        THEN("Exception appears - 1") {
            stream << "functio";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 2") {
            stream << "function 01";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 3") {
            stream << "function fun";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 4") {
            stream << "function fun dd";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 5") {
            stream << "function fun(";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 6") {
            stream << "function fun(01";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 7") {
            stream << "function fun()";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 8") {
            stream << "function fun()[";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 9") {
            stream << "function fun(){";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 10") {
            stream << "function fun(){}"
                      "11";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 10") {
            stream << "function fun(){}"
                      "function";
            REQUIRE_THROWS(parser.parse());
        }
    }

    WHEN("Correct function definition") {
        THEN("Exception appears - don't contain main - 1") {
            stream << "function func() {}";
            parser.parse();
            REQUIRE_THROWS_WITH(parser.run(), Contains("main"));
        }
        THEN("Exception appears - don't contain main") {
            stream << "function func(a, b, c, d) {}";
            parser.parse();
            REQUIRE_THROWS_WITH(parser.run(), Contains("main"));
        }
        THEN("works - Contain main function") {
            stream << "function main() {}";
            parser.parse();
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("works - Contain 2 function") {
            stream << "function func() {}"
                      "function main() {}";
            parser.parse();
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("works - Contain 3 function") {
            stream << "function func() {}"
                      "function func() {}"
                      "function main() {}";
            parser.parse();
            REQUIRE_NOTHROW(parser.run());
        }
    }
}

SCENARIO("InitStatement definition", "[Parser]") {
    std::string streamValue = " ";
    std::stringstream stream(streamValue);
    std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(stream);
    Parser parser(std::move(lexer));

    WHEN("Wrong initStatement definition") {
        THEN("Exception appears - 1") {
            stream << "function func() {"
                      "var"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 2") {
            stream << "function func() {"
                      "var a"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 3") {
            stream << "function func() {"
                      "var a ="
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 4") {
            stream << "function func() {"
                      "var a = 2"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
    }

    WHEN("Correct initStatement definition") {
        THEN("it works - var a") {
            stream << "function main() {"
                      "var a;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("it works - var a = 2") {
            stream << "function main() {"
                      "var a = 2;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("it works - var a = b") {
            stream << "function main() {"
                      "var b = 2;"
                      "var a = b;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("it not work - double declaration - 1") {
            stream << "function main() {"
                      "var a;"
                      "var a;"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("it not work - double declaration - 2") {
            stream << "function main() {"
                      "var a = 2;"
                      "var a;"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("it not work - double declaration - 3") {
            stream << "function main() {"
                      "var a;"
                      "var a = 2;"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
    }
}

SCENARIO("IfStatement definition", "[Parser]") {
    std::string streamValue = " ";
    std::stringstream stream(streamValue);
    std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(stream);
    Parser parser(std::move(lexer));
    WHEN("Wrong ifStatement definition") {
        THEN("Exception appears - 1") {
            stream << "function func() {"
                      "if"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 2") {
            stream << "function func() {"
                      "if("
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 3") {
            stream << "function func() {"
                      "if(2"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 4") {
            stream << "function func() {"
                      "if(v"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 5") {
            stream << "function func() {"
                      "if(2)"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 6") {
            stream << "function func() {"
                      "if(2){"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 7") {
            stream << "function func() {"
                      "if(2){2}"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 8") {
            stream << "function func() {"
                      "if(2){}"
                      "else"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 9") {
            stream << "function func() {"
                      "if(2){}"
                      "else{2"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
    }

    WHEN("Correct ifStatement definition") {
        THEN("it works - if") {
            stream << "function main() {"
                      "if(2){}"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("it works - if + else") {
            stream << "function main() {"
                      "if(2){}"
                      "else{}"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("it works - if + variable") {
            stream << "function main() {"
                      "var a = 2;"
                      "if(a){}"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
    }
}

SCENARIO("WhileStatement definition", "[Parser]") {
    std::string streamValue = " ";
    std::stringstream stream(streamValue);
    std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(stream);
    Parser parser(std::move(lexer));
    WHEN("Wrong whileStatement definition") {
        THEN("Exception appears - 1") {
            stream << "function func() {"
                      "while"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 2") {
            stream << "function func() {"
                      "while("
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 3") {
            stream << "function func() {"
                      "while(2"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 4") {
            stream << "function func() {"
                      "while(v"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 5") {
            stream << "function func() {"
                      "while(2)"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 6") {
            stream << "function func() {"
                      "while(2){"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
    }

    WHEN("Correct whileStatement definition") {
        THEN("it works") {
            stream << "function main() {"
                      "while(!2){}"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("it works + wariable") {
            stream << "function main() {"
                      "var a;"
                      "while(a){}"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
    }
}

SCENARIO("ReturnStatement definition", "[Parser]") {
    std::string streamValue = " ";
    std::stringstream stream(streamValue);
    std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(stream);
    Parser parser(std::move(lexer));

    WHEN("Wrong returnStatement definition") {
        THEN("Exception appears - 1") {
            stream << "function func() {"
                      "return"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 2") {
            stream << "function func() {"
                      "return ("
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 3") {
            stream << "function func() {"
                      "return 2"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
    }

    WHEN("Correct returnStatement definition") {
        THEN("it works") {
            stream << "function main() {"
                      "return 2;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
    }
}

SCENARIO("AssignStatement definition", "[Parser]") {
    std::string streamValue = " ";
    std::stringstream stream(streamValue);
    std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(stream);
    Parser parser(std::move(lexer));

    WHEN("Wrong assignStatement definition") {
        THEN("Exception appears - 1") {
            stream << "function func() {"
                      "var a;"
                      "a"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 2") {
            stream << "function func() {"
                      "var a;"
                      "a="
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 3") {
            stream << "function func() {"
                      "var a;"
                      "a=2"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
    }

    WHEN("correct assignStatement definition") {
        THEN("it works") {
            stream << "function main() {"
                      "var a;"
                      "a=2;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
    }
}

SCENARIO("FunctionCall definition", "[Parser]") {
    std::string streamValue = " ";
    std::stringstream stream(streamValue);
    std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(stream);
    Parser parser(std::move(lexer));

    WHEN("Wrong functionCall definition") {
        THEN("Exception appears - 1") {
            stream << "function func() {}"
                      "function main() {"
                      "func"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 2") {
            stream << "function func() {}"
                      "function main() {"
                      "func("
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 3") {
            stream << "function func() {}"
                      "function main() {"
                      "func()"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
    }

    WHEN("Correct functionCall definition") {
        THEN("it works - 0 parameters") {
            stream << "function func() {}"
                      "function main() {"
                      "func();"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("Exception appears - wrong number of parameters - 1") {
            stream << "function func() {}"
                      "function main() {"
                      "func(1);"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - wrong number of parameters - 2") {
            stream << "function func() {}"
                      "function main() {"
                      "func(1,2);"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("it works - 1 parameter") {
            stream << "function func(a) {}"
                      "function main() {"
                      "func(1);"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("Exception appears - wrong number of parameters - 3") {
            stream << "function func(a) {}"
                      "function main() {"
                      "func();"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - wrong number of parameters - 4") {
            stream << "function func(a) {}"
                      "function main() {"
                      "func(1,2);"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("it works - 2 parameters") {
            stream << "function func(a,b) {}"
                      "function main() {"
                      "func(1,2);"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("Exception appears - wrong number of parameters - 5") {
            stream << "function func(a,b) {}"
                      "function main() {"
                      "func();"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - wrong number of parameters - 6") {
            stream << "function func(a,b) {}"
                      "function main() {"
                      "func(1);"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
    }
}

SCENARIO("_continue & _break definitions", "[Parser]") {
    std::string streamValue = " ";
    std::stringstream stream(streamValue);
    std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(stream);
    Parser parser(std::move(lexer));

    WHEN("wrong _continue definition") {
        THEN("Exception appears - 1") {
            stream << "function func() {"
                      "continue"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
    }

    WHEN("Correct _continue definition") {
        THEN("it works") {
            stream << "function main() {"
                      "continue;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
    }

    WHEN("Wrong _break definition") {
        THEN("Exception appears - 1") {
            stream << "function func() {"
                      "break"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
    }

    WHEN("Correct _break definition") {
        THEN("it works") {
            stream << "function main() {"
                      "break;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
    }
}

SCENARIO("PrintStatement definition", "[Parser]") {
    std::string streamValue = " ";
    std::stringstream stream(streamValue);
    std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(stream);
    Parser parser(std::move(lexer));
    Printer::instance().setEnableOutput(false);

    WHEN("Wrong printStatement definition") {
        THEN("Exception appears - 1") {
            stream << "function func() {"
                      "print"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 2") {
            stream << "function func() {"
                      "print("
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 3") {
            stream << "function func() {"
                      "print(1"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 4") {
            stream << "function func() {"
                      "print(1)"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 5") {
            stream << "function func() {"
                      "print();"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 6") {
            stream << "function func() {"
                      "print(1,);"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 7") {
            stream << "function func() {"
                      "print(\"text\",);"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 8") {
            stream << "function func() {"
                      "print(1,2)"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 9") {
            stream << "function func() {"
                      "print(1,2,);"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 10") {
            stream << "function func() {"
                      "print(1,2,3)"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
    }

    WHEN("Correct printStatement definition") {
        THEN("it works - expression") {
            stream << "function main() {"
                      "print(1);"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("it works - expression, string") {
            stream << "function main() {"
                      "print(1,\"text\");"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("it works - expression, string, expression") {
            stream << "function main() {"
                      "print(1,\"text\",2);"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("it works - string") {
            stream << "function main() {"
                      "print(\"text\");"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("it works - string, expression") {
            stream << "function main() {"
                      "print(\"text\",2);"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("it works - string, expression, string") {
            stream << "function main() {"
                      "print(\"text\",2,\"text\");"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
    }
}

SCENARIO("StatementBlock definition", "[Parser]") {
    std::string streamValue = " ";
    std::stringstream stream(streamValue);
    std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(stream);
    Parser parser(std::move(lexer));

    WHEN("Wrong statementBlock definition") {
        THEN("Exception appears - 1") {
            stream << "function func() {"
                      "{"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 2") {
            stream << "function func() {"
                      "{}"
                      "{"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 3") {
            stream << "function func() {"
                      "{{}"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
    }

    WHEN("Correct statementBlock definition") {
        THEN("it works - 1") {
            stream << "function main() {"
                      "{}"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("it works - 2") {
            stream << "function main() {"
                      "{return 1;}"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("it works - 3") {
            stream << "function main() {"
                      "{{}}"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("it works - 4") {
            stream << "function main() {"
                      "{{return 1;}}"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
    }
}


SCENARIO("LogicExpr definition", "[Parser]") {
    std::string streamValue = " ";
    std::stringstream stream(streamValue);
    std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(stream);
    Parser parser(std::move(lexer));

    WHEN("Wrong logicExpr definition") {
        THEN("Exception appears - 1") {
            stream << "function func() {"
                      "return 1||;"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 2") {
            stream << "function func() {"
                      "return 1||2||;"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 3") {
            stream << "function func() {"
                      "return 1||2||3||;"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
    }

    WHEN("Correct logicExpr definition") {
        THEN("it works - 2 arguments") {
            stream << "function main() {"
                      "return 1||2;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("it works - 3 arguments") {
            stream << "function main() {"
                      "return 1||2||3;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("it works - 4 arguments") {
            stream << "function main() {"
                      "return 1||2||3||4;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
    }
}

SCENARIO("AndExpr definition", "[Parser]") {
    std::string streamValue = " ";
    std::stringstream stream(streamValue);
    std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(stream);
    Parser parser(std::move(lexer));

    GIVEN("Wrong andExpr definition") {
        THEN("Exception appears - 1") {
            stream << "function func() {"
                      "return 1&&;"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 2") {
            stream << "function func() {"
                      "return 1&&2&&;"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 3") {
            stream << "function func() {"
                      "return 1&&2&&3&&;"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
    }

    GIVEN("Correct andExpr definition") {
        THEN("it works - 2 arguments") {
            stream << "function main() {"
                      "return 1&&2;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("it works - 3 arguments") {
            stream << "function main() {"
                      "return 1&&2&&3;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("it works - 4 arguments") {
            stream << "function main() {"
                      "return 1&&2&&3&&4;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
    }
}

SCENARIO("relationalExpr definition", "[Parser]") {
    std::string streamValue = " ";
    std::stringstream stream(streamValue);
    std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(stream);
    Parser parser(std::move(lexer));

    WHEN("Wrong relationalExpr definition") {
        THEN("Exception appears - 1") {
            stream << "function func() {"
                      "return 1==;"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 2") {
            stream << "function func() {"
                      "return 1!=;"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 3") {
            stream << "function func() {"
                      "return 1<;"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 4") {
            stream << "function func() {"
                      "return 1>;"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 5") {
            stream << "function func() {"
                      "return 1<=;"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 6") {
            stream << "function func() {"
                      "return 1>=;"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 7") {
            stream << "function func() {"
                      "return 1==1==;"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 8") {
            stream << "function func() {"
                      "return 1!=2!=;"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 9") {
            stream << "function func() {"
                      "return 1<2<;"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 10") {
            stream << "function func() {"
                      "return 1>2>;"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 11") {
            stream << "function func() {"
                      "return 1<=2<=;"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 12") {
            stream << "function func() {"
                      "return 1>=2>=;"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
    }

    WHEN("Correct relationalExpr definition") {
        THEN("it works - Equality") {
            stream << "function main() {"
                      "return 1==2;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("it works - Inequality") {
            stream << "function main() {"
                      "return 1!=2;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("it works - Less") {
            stream << "function main() {"
                      "return 1<2;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("it works - Greater") {
            stream << "function main() {"
                      "return 1>2;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("it works - LessOrEqual") {
            stream << "function main() {"
                      "return 1<=2;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("it works - GreaterOrEqual") {
            stream << "function main() {"
                      "return 1>=2;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
    }
}

SCENARIO("BaseLogicExpr definition", "[Parser]") {
    std::string streamValue = " ";
    std::stringstream stream(streamValue);
    std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(stream);
    Parser parser(std::move(lexer));

    WHEN("Wrong baseLogicExpr definition") {
        THEN("Exception appears - 1") {
            stream << "function func() {"
                      "return !"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 2") {
            stream << "function func() {"
                      "return !!1"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
    }

    WHEN("Correct baseLogicExpr definition") {
        THEN("it works") {
            stream << "function main() {"
                      "return !1;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
    }
}

SCENARIO("MathExpr definition", "[Parser]") {
    std::string streamValue = " ";
    std::stringstream stream(streamValue);
    std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(stream);
    Parser parser(std::move(lexer));

    WHEN("Wrong mathExpr definition") {
        THEN("Exception appears - 1") {
            stream << "function func() {"
                      "return 1+"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 2") {
            stream << "function func() {"
                      "return 1+2+"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 3") {
            stream << "function func() {"
                      "return 1+2+3+"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 4") {
            stream << "function func() {"
                      "return 1-"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 5") {
            stream << "function func() {"
                      "return 1-2-"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 6") {
            stream << "function func() {"
                      "return 1-2-3-"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
    }

    WHEN("Correct mathExpr definition") {
        THEN("it works - Plus - 2 arguments") {
            stream << "function main() {"
                      "return 1+2;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("it works - Plus - 3 arguments") {
            stream << "function main() {"
                      "return 1+2+3;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("it works - Plus - 4 arguments") {
            stream << "function main() {"
                      "return 1+2+3+4;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("it works - Minus - 2 arguments") {
            stream << "function main() {"
                      "return 1-2;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("it works - Minus - 3 arguments") {
            stream << "function main() {"
                      "return 1-2-3;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("it works - Minus - 4 arguments") {
            stream << "function main() {"
                      "return 1-2-3-4;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
    }
}

SCENARIO("MultiplicativeExpr definition", "[Parser]") {
    std::string streamValue = " ";
    std::stringstream stream(streamValue);
    std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(stream);
    Parser parser(std::move(lexer));

    WHEN("Wrong multiplicativeExpr definition") {
        THEN("Exception appears - 1") {
            stream << "function func() {"
                      "return 1*"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 2") {
            stream << "function func() {"
                      "return 1*2*"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 3") {
            stream << "function func() {"
                      "return 1*2*3*"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 4") {
            stream << "function func() {"
                      "return 1/"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 5") {
            stream << "function func() {"
                      "return 1/2/"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 6") {
            stream << "function func() {"
                      "return 1/2/3/"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 7") {
            stream << "function func() {"
                      "return 1%"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 8") {
            stream << "function func() {"
                      "return 1%2%"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 9") {
            stream << "function func() {"
                      "return 1%2%3%"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
    }

    WHEN("Correct mathExpr definition") {
        THEN("it works - Multiply - 2 arguments") {
            stream << "function main() {"
                      "return 1*2;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("it works - Multiply - 3 arguments") {
            stream << "function main() {"
                      "return 1*2*3;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("it works - Multiply - 4 arguments") {
            stream << "function main() {"
                      "return 1*2*3*4;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("it works - Divide - 2 arguments") {
            stream << "function main() {"
                      "return 1/2;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("it works - Divide - 3 arguments") {
            stream << "function main() {"
                      "return 1/2/3;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("it works - Divide - 4 arguments") {
            stream << "function main() {"
                      "return 1/2/3/4;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("it works - Modulo - 2 arguments") {
            stream << "function main() {"
                      "return 1%2;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("it works - Modulo - 3 arguments") {
            stream << "function main() {"
                      "return 1%2%3;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("it works - Modulo - 4 arguments") {
            stream << "function main() {"
                      "return 1%2%3%4;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
    }
}

SCENARIO("BaseMathExpr definition", "[Parser]") {
    std::string streamValue = " ";
    std::stringstream stream(streamValue);
    std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(stream);
    Parser parser(std::move(lexer));

    WHEN("Wrong baseMathExpr definition") {
        THEN("Exception appears - 1") {
            stream << "function func() {"
                      "return "
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 2") {
            stream << "function func() {"
                      "return vec"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 3") {
            stream << "function func() {"
                      "return vec("
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 4") {
            stream << "function func() {"
                      "return vec(1"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 5") {
            stream << "function func() {"
                      "return vec(1,"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 6") {
            stream << "function func() {"
                      "return vec(1,2"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 7") {
            stream << "function func() {"
                      "return vec(1,2)"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 8") {
            stream << "function func() {"
                      "return vec(1,2,"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 9") {
            stream << "function func() {"
                      "return vec(1,2,3"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 10") {
            stream << "function func() {"
                      "return vec(1,2,3)"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 11") {
            stream << "function func() {"
                      "return variable"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 12") {
            stream << "function func() {"
                      "return variable["
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 13") {
            stream << "function func() {"
                      "return variable[1"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 14") {
            stream << "function func() {"
                      "return variable[1]"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 15") {
            stream << "function func() {"
                      "return f()"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 16") {
            stream << "function func() {"
                      "return f("
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("Exception appears - 17") {
            stream << "function func() {"
                      "return f()"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
    }

    WHEN("Correct baseMathExpr definition") {
        THEN("it works - numberLiteral") {
            stream << "function main() {"
                      "return 1;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("it works - numberLiteral + unaryMathOp") {
            stream << "function main() {"
                      "return -1;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("it works - vectorLiteral 2d") {
            stream << "function main() {"
                      "return vec(1,2);"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("it works - vectorLiteral 2d + unaryMathOp") {
            stream << "function main() {"
                      "return -vec(1,2);"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("it works - vectorLiteral 3d") {
            stream << "function main() {"
                      "return vec(1,2,3);"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("it works - vectorLiteral 3d + unaryMathOp") {
            stream << "function main() {"
                      "return -vec(1,2,3);"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("Exception appears - variable not defined") {
            stream << "function func() {"
                      "return a;"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("it works - variable") {
            stream << "function main() {"
                      "var a=1;"
                      "return a;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("it works - variable + unaryMathOp") {
            stream << "function main() {"
                      "var a=1;"
                      "return -a;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("Exception appears - function not defined") {
            stream << "function func() {"
                      "return a();"
                      "}";
            REQUIRE_THROWS(parser.parse());
        }
        THEN("it works - functionCall") {
            stream << "function a() {}"
                      "function main() {"
                      "return a();"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("it works - functionCall + unaryMathOp") {
            stream << "function a() {}"
                      "function main() {"
                      "return a();"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("Exception appears - variable not defined") {
            stream << "function main() {"
                      "return (1);"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
        THEN("Exception appears - variable not defined") {
            stream << "function main() {"
                      "return ((1));"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE_NOTHROW(parser.run());
        }
    }
}

SCENARIO("Math logic", "[Parser]") {
    std::string streamValue = " ";
    std::stringstream stream(streamValue);
    std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(stream);
    Parser parser(std::move(lexer));

    WHEN("Correct math logic") {
        THEN("it works - 1") {
            stream << "function main() {"
                      "return 1+2*2;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE(parser.run().variable == Variable({5}));
        }
        THEN("it works - 2") {
            stream << "function main() {"
                      "return 1+2*2+1;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE(parser.run().variable == Variable({6}));
        }
        THEN("it works - 3") {
            stream << "function main() {"
                      "return -1+2*2;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE(parser.run().variable == Variable({3}));
        }
        THEN("it works - 4") {
            stream << "function main() {"
                      "return -(1+2*2);"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE(parser.run().variable == Variable({-5}));
        }
        THEN("it works - 5") {
            stream << "function main() {"
                      "return !(1+2*2);"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE(parser.run().variable == Variable());
        }
        THEN("it works - 6") {
            stream << "function main() {"
                      "return 2*2-1 == -1+2*2;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE(parser.run().variable == Variable({1}));
        }
        THEN("it works - 7") {
            stream << "function main() {"
                      "return 2*2-1 != 2*2+1;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE(parser.run().variable == Variable({1}));
        }
        THEN("it works - 8") {
            stream << "function main() {"
                      "return 2*2-1 < 2*2+1;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE(parser.run().variable == Variable({1}));
        }
        THEN("it works - 9") {
            stream << "function main() {"
                      "return 2*2-1 > 2*2+1;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE(parser.run().variable == Variable());
        }
        THEN("it works - 10") {
            stream << "function main() {"
                      "return 2*2-1 <= 2*2+1;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE(parser.run().variable == Variable({1}));
        }
        THEN("it works - 11") {
            stream << "function main() {"
                      "return 2*2-1 >= 2*2+1;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE(parser.run().variable == Variable());
        }
        THEN("it works - 12") {
            stream << "function main() {"
                      "return 2*2-1 && 2*2+1;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE(parser.run().variable == Variable({1}));
        }
        THEN("it works - 13") {
            stream << "function main() {"
                      "return 2*2-1 && !(2*2+1);"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE(parser.run().variable == Variable());
        }
        THEN("it works - 14") {
            stream << "function main() {"
                      "return 2*2-1 || 2*2+1;"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE(parser.run().variable == Variable({1}));
        }
        THEN("it works - 15") {
            stream << "function main() {"
                      "return 2*2-1 || !(2*2+1);"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE(parser.run().variable == Variable({1}));
        }
        THEN("it works - 16") {
            stream << "function main() {"
                      "return !(2*2-1) || !(2*2+1);"
                      "}";
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE(parser.run().variable == Variable());
        }
    }
}
