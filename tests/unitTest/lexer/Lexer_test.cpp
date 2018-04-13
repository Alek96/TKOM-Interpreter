#include <catch.hpp>
#include <sstream>
#include "lexer/Lexer.hpp"
#include "token/TokenType.hpp"
#include "token/TokenTypeDefiner.hpp"
#include "exception/Exception.hpp"

using namespace tkom;

SCENARIO("Test for Lexer","[Lexer]") {
    GIVEN("Stream without a data") {
        std::string streamValue = "";
        std::istringstream istream(streamValue);

        Lexer lexer(istream);
        WHEN("Read the Stream") {
            THEN("First get return Invalid Token") {
                REQUIRE(lexer.getToken().type == TokenType::Invalid);
            }
            THEN("Token EOF is read") {
                lexer.readNextToken();
                REQUIRE(lexer.getToken().type == TokenType::EndOfFile);
            }
        }
    }
    GIVEN("Stream with a white data") {
        std::string streamValue = " \n";
        std::istringstream istream(streamValue);

        Lexer lexer(istream);
        WHEN("Read the Stream") {
            THEN("Token EOF is read") {
                lexer.readNextToken();
                REQUIRE(lexer.getToken().type == TokenType::EndOfFile);
            }
        }
    }
    GIVEN("Stream with a Keywords data") {
        std::string streamValue = "function "
                                  "if "
                                  "while "
                                  "else "
                                  "return "
                                  "continue "
                                  "break "
                                  "literal "
                                  "vec "
                                  "print ";
        std::istringstream istream(streamValue);

        Lexer lexer(istream);
        WHEN("Read the Stream") {
            THEN("Token are read") {
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::Function);
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::If);
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::While);
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::Else);
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::Return);
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::Continue);
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::Break);
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::Var);
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::Vec);
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::Print);
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::EndOfFile);
            }
        }
    }
    GIVEN("Stream with a Identifiers data") {
        std::string streamValue = "a "
                                  "bc "
                                  "def "
                                  "ghij ";
        std::istringstream istream(streamValue);

        Lexer lexer(istream);
        WHEN("Read the Stream") {
            THEN("Token are read") {
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::Identifier);
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::Identifier);
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::Identifier);
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::Identifier);
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::EndOfFile);
            }
        }
    }
    GIVEN("Stream with a Numbers data") {
        std::string streamValue = "0 "
                                  "12 "
                                  "345 "
                                  "6789 ";
        std::istringstream istream(streamValue);

        Lexer lexer(istream);
        WHEN("Read the Stream") {
            THEN("Token are read") {
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::NumberLiteral);
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::NumberLiteral);
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::NumberLiteral);
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::NumberLiteral);
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::EndOfFile);
            }
        }
    }
    GIVEN("Stream with a data with special character") {
        std::string streamValue = "( "
                                  ") "
                                  "[ "
                                  "] "
                                  "{ "
                                  "} "
                                  ", "
                                  "= "
                                  "; "

                                  "! "
                                  "|| "
                                  "&& "
                                  "== "
                                  "!= "
                                  "< "
                                  "> "
                                  "<= "
                                  ">= "
                                  "+ "
                                  "- "
                                  "* "
                                  "/ "
                                  "% ";
        std::istringstream istream(streamValue);

        Lexer lexer(istream);
        WHEN("Read the Stream") {
            THEN("Token are read") {
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::ParenthesisOpen);
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::ParenthesisClose);
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::BracketOpen);
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::BracketClose);
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::CurlyBracketOpen);
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::CurlyBracketClose);
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::Comma);
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::Assignment);
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::Semicolon);

                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::Negation);
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::Or);
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::And);
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::Equality);
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::Inequality);
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::Less);
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::Greater);
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::LessOrEqual);
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::GreaterOrEqual);
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::Plus);
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::Minus);
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::Multiply);
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::Divide);
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::Modulo);

                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::EndOfFile);
            }
        }
    }

    GIVEN("Stream with a data with special character") {
        std::string streamValue = "  ";
        std::stringstream stream(streamValue);
        Lexer lexer(stream);

        WHEN("Character '(' appears") {
            THEN("Token ParenthesisOpen is read") {
                stream << "(";
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::ParenthesisOpen);
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::EndOfFile);
            }
        }
        WHEN("Character ')' appears") {
            stream << ")";
            THEN("Token ParenthesisClose is read") {
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::ParenthesisClose);
                lexer.readNextToken(); REQUIRE(lexer.getToken().type == TokenType::EndOfFile);
            }
        }
    }
    GIVEN("Stream with a \" character") {
        std::string streamValue = "";
        std::stringstream stream(streamValue);
        Lexer lexer(stream);

        WHEN("Characters '\" \"' appears, with some text inside") {
            std::string message = "text";
            stream << "\"" << message << "\"";
            THEN("Token StringLiteral is read") {
                lexer.readNextToken();
                REQUIRE(lexer.getToken().type == TokenType::StringLiteral);
                REQUIRE(lexer.getToken().value == message);
            }
        }
        WHEN("Characters '\" \"' appears, with some text and '\\n' inside") {
            std::string message = "text\ntext\n";
            stream << "\"" << message << "\"";
            THEN("Token StringLiteral is read") {
                lexer.readNextToken();
                REQUIRE(lexer.getToken().type == TokenType::StringLiteral);
                REQUIRE(lexer.getToken().value == message);
            }
        }
        WHEN("Characters '\" \"' appears, with some text and '\"' inside") {
            std::string message = "text";
            stream << R"("\")" << message <<  R"(\"")";
            THEN("Token StringLiteral is read") {
                lexer.readNextToken();
                REQUIRE(lexer.getToken().type == TokenType::StringLiteral);
                REQUIRE(lexer.getToken().value == "\"" + message + "\"");
            }
        }
        WHEN("One character '\"' appears, without second '\"'") {
            std::string message = "text";
            stream << "\"" << message;
            THEN("Exception is throw") {
                REQUIRE_THROWS_AS(lexer.readNextToken(), InvalidTokenException);
                REQUIRE(lexer.getToken().type == TokenType::Invalid);
                REQUIRE(lexer.getToken().value == message);
            }
        }
    }

    GIVEN("Stream with a non defined character") {
        std::string streamValue = "";
        std::stringstream stream(streamValue);
        Lexer lexer(stream);

        WHEN("Character & appears") {
            std::string message = "&";
            stream << message;
            THEN("Token StringLiteral is read") {
                REQUIRE_THROWS_AS(lexer.readNextToken(), InvalidTokenException);
                REQUIRE(lexer.getToken().type == TokenType::Invalid);
                REQUIRE(lexer.getToken().value == message);
            }
        }
        WHEN("Character | appears") {
            std::string message = "|";
            stream << message;
            THEN("Token StringLiteral is read") {
                REQUIRE_THROWS_AS(lexer.readNextToken(), InvalidTokenException);
                REQUIRE(lexer.getToken().type == TokenType::Invalid);
                REQUIRE(lexer.getToken().value == message);
            }
        }
    }
}