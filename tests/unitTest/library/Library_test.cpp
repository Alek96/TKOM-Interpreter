#include <catch.hpp>
#include <sstream>
#include "library/Library.hpp"
#include "lexer/Lexer.hpp"
#include "parser/Parser.hpp"

using namespace tkom;

SCENARIO("Test for Library","[Library]") {
    tkom::Parser parser;
    tkom::Library library(parser);

    std::string streamValue = " ";
    std::stringstream stream(streamValue);
    parser.setLexer(std::make_unique<tkom::Lexer>(stream));
    WHEN("Using function convertFrom2dTo3d") {
        stream << "function main() { \n"
                  " return convertFrom2dTo3d(vec(1,1)); \n"
                  "}";
        THEN("is returning vector 3d - 1") {
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE(parser.run().variable == ast::Variable({1,1,0}));
        }
    }
    WHEN("Using function convertFrom2dTo3d") {
        stream << "function main() { \n"
                  " return convertFrom2dTo3d(vec(1,2)); \n"
                  "}";
        THEN("is returning vector 3d - 2") {
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE(parser.run().variable == ast::Variable({1,2,0}));
        }
    }

    WHEN("Using function convertFrom3dTo2d") {
        stream << "function main() { \n"
                  " return convertFrom3dTo2d(vec(1,1,1)); \n"
                  "}";
        THEN("is returning vector 2d - 1") {
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE(parser.run().variable == ast::Variable({1,1}));
        }
    }
    WHEN("Using function convertFrom3dTo2d") {
        stream << "function main() { \n"
                  " return convertFrom3dTo2d(vec(1,2,3)); \n"
                  "}";
        THEN("is returning vector 2d - 2") {
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE(parser.run().variable == ast::Variable({1,2}));
        }
    }

    WHEN("Using function crossProduct2") {
        stream << "function main() { \n"
                  " return crossProduct2(vec(1,2),vec(1,2)); \n"
                  "}";
        THEN("is returning cross product vector 2d - 1") {
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE(parser.run().variable == ast::Variable({0,0}));
        }
    }
    WHEN("Using function crossProduct2") {
        stream << "function main() { \n"
                  " return crossProduct2(vec(1,2),vec(2,1)); \n"
                  "}";
        THEN("is returning cross product vector 2d - 2") {
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE(parser.run().variable == ast::Variable({1,1}));
        }
    }

    WHEN("Using function crossProduct3") {
        stream << "function main() { \n"
                  " return crossProduct3(vec(1,2,3),vec(1,2,3)); \n"
                  "}";
        THEN("is returning cross product vector 3d - 1") {
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE(parser.run().variable == ast::Variable({0,0,0}));
        }
    }
    WHEN("Using function crossProduct3") {
        stream << "function main() { \n"
                  " return crossProduct3(vec(1,2,3),vec(4,5,6)); \n"
                  "}";
        THEN("is returning cross product vector 3d - 2") {
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE(parser.run().variable == ast::Variable({-3,6,-3}));
        }
    }

    WHEN("Using function scalarProduct2") {
        stream << "function main() { \n"
                  " return scalarProduct2(vec(1,2),vec(1,2)); \n"
                  "}";
        THEN("is returning scalar product - 1") {
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE(parser.run().variable == ast::Variable({5}));
        }
    }
    WHEN("Using function scalarProduct2") {
        stream << "function main() { \n"
                  " return scalarProduct2(vec(1,2),vec(3,4)); \n"
                  "}";
        THEN("is returning scalar product - 2") {
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE(parser.run().variable == ast::Variable({11}));
        }
    }

    WHEN("Using function scalarProduct3") {
        stream << "function main() { \n"
                  " return scalarProduct3(vec(1,2,3),vec(1,2,3)); \n"
                  "}";
        THEN("is returning scalar product - 1") {
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE(parser.run().variable == ast::Variable({14}));
        }
    }
    WHEN("Using function scalarProduct3") {
        stream << "function main() { \n"
                  " return scalarProduct3(vec(1,2,3),vec(4,5,6)); \n"
                  "}";
        THEN("is returning scalar product - 2") {
            REQUIRE_NOTHROW(parser.parse());
            REQUIRE(parser.run().variable == ast::Variable({32}));
        }
    }
}