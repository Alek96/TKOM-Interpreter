#include <catch.hpp>
#include "Token/TokenTypeDefiner.hpp"

using namespace tkom;

SCENARIO("Test for TokenTypeDefiner", "[TokenTypeDefiner][TokenType]") {

    THEN("Test all existing elements") {
        //Keywords
        REQUIRE(TokenTypeDefiner::exist("function"));
        REQUIRE(TokenTypeDefiner::exist("if"));
        REQUIRE(TokenTypeDefiner::exist("while"));
        REQUIRE(TokenTypeDefiner::exist("else"));
        REQUIRE(TokenTypeDefiner::exist("return"));
        REQUIRE(TokenTypeDefiner::exist("continue"));
        REQUIRE(TokenTypeDefiner::exist("break"));
        REQUIRE(TokenTypeDefiner::exist("literal"));
        REQUIRE(TokenTypeDefiner::exist("vec"));
        REQUIRE(TokenTypeDefiner::exist("print"));

        //Siple Sign
        REQUIRE(TokenTypeDefiner::exist('('));
        REQUIRE(TokenTypeDefiner::exist(')'));
        REQUIRE(TokenTypeDefiner::exist('['));
        REQUIRE(TokenTypeDefiner::exist(']'));
        REQUIRE(TokenTypeDefiner::exist('{'));
        REQUIRE(TokenTypeDefiner::exist('}'));
        REQUIRE(TokenTypeDefiner::exist(','));
        REQUIRE(TokenTypeDefiner::exist('='));
        REQUIRE(TokenTypeDefiner::exist(';'));

        REQUIRE(TokenTypeDefiner::exist('!'));
        REQUIRE(TokenTypeDefiner::exist('+'));
        REQUIRE(TokenTypeDefiner::exist('-'));
        REQUIRE(TokenTypeDefiner::exist('*'));
        REQUIRE(TokenTypeDefiner::exist('/'));
        REQUIRE(TokenTypeDefiner::exist('%'));
    }
    THEN("Test some not existing elements") {
        REQUIRE_FALSE(TokenTypeDefiner::exist("functio"));
        REQUIRE_FALSE(TokenTypeDefiner::exist("ifs"));

        REQUIRE_FALSE(TokenTypeDefiner::exist('a'));
        REQUIRE_FALSE(TokenTypeDefiner::exist('b'));
    }
    THEN("Find all existing elements") {
        //Keywords
        REQUIRE(TokenTypeDefiner::find("function") == TokenType::Function);
        REQUIRE(TokenTypeDefiner::find("if") == TokenType::If);
        REQUIRE(TokenTypeDefiner::find("while") == TokenType::While);
        REQUIRE(TokenTypeDefiner::find("else") == TokenType::Else);
        REQUIRE(TokenTypeDefiner::find("return") == TokenType::Return);
        REQUIRE(TokenTypeDefiner::find("continue") == TokenType::Continue);
        REQUIRE(TokenTypeDefiner::find("break") == TokenType::Break);
        REQUIRE(TokenTypeDefiner::find("literal") == TokenType::Var);
        REQUIRE(TokenTypeDefiner::find("vec") == TokenType::Vec);
        REQUIRE(TokenTypeDefiner::find("print") == TokenType::Print);

        //Simple Sign
        REQUIRE(TokenTypeDefiner::find('(') == TokenType::ParenthesisOpen);
        REQUIRE(TokenTypeDefiner::find(')') == TokenType::ParenthesisClose);
        REQUIRE(TokenTypeDefiner::find('[') == TokenType::BracketOpen);
        REQUIRE(TokenTypeDefiner::find(']') == TokenType::BracketClose);
        REQUIRE(TokenTypeDefiner::find('{') == TokenType::CurlyBracketOpen);
        REQUIRE(TokenTypeDefiner::find('}') == TokenType::CurlyBracketClose);
        REQUIRE(TokenTypeDefiner::find(',') == TokenType::Comma);
        REQUIRE(TokenTypeDefiner::find('=') == TokenType::Assignment);
        REQUIRE(TokenTypeDefiner::find(';') == TokenType::Semicolon);

        REQUIRE(TokenTypeDefiner::find('!') == TokenType::Negation);
        REQUIRE(TokenTypeDefiner::find('+') == TokenType::Plus);
        REQUIRE(TokenTypeDefiner::find('-') == TokenType::Minus);
        REQUIRE(TokenTypeDefiner::find('*') == TokenType::Multiply);
        REQUIRE(TokenTypeDefiner::find('/') == TokenType::Divide);
        REQUIRE(TokenTypeDefiner::find('%') == TokenType::Modulo);
    }

    THEN("Not find elements that not exist and return Token::Invalid") {
        REQUIRE(TokenTypeDefiner::find("functio") == TokenType::Invalid);
        REQUIRE(TokenTypeDefiner::find("ifs") == TokenType::Invalid);

        REQUIRE(TokenTypeDefiner::find('a') == TokenType::Invalid);
        REQUIRE(TokenTypeDefiner::find('b') == TokenType::Invalid);
    }

    THEN("Test all Names") {
        REQUIRE(TokenTypeDefiner::getName(TokenType::Function) == "Function");
        REQUIRE(TokenTypeDefiner::getName(TokenType::If) == "If");
        REQUIRE(TokenTypeDefiner::getName(TokenType::While) == "While");
        REQUIRE(TokenTypeDefiner::getName(TokenType::Else) == "Else");
        REQUIRE(TokenTypeDefiner::getName(TokenType::Return) == "Return");
        REQUIRE(TokenTypeDefiner::getName(TokenType::Continue) == "Continue");
        REQUIRE(TokenTypeDefiner::getName(TokenType::Var) == "Var");
        REQUIRE(TokenTypeDefiner::getName(TokenType::Vec) == "Vec");
        REQUIRE(TokenTypeDefiner::getName(TokenType::Print) == "Print");

        REQUIRE(TokenTypeDefiner::getName(TokenType::ParenthesisOpen) == "ParenthesisOpen");
        REQUIRE(TokenTypeDefiner::getName(TokenType::ParenthesisClose) == "ParenthesisClose");
        REQUIRE(TokenTypeDefiner::getName(TokenType::BracketOpen) == "BracketOpen");
        REQUIRE(TokenTypeDefiner::getName(TokenType::BracketClose) == "BracketClose");
        REQUIRE(TokenTypeDefiner::getName(TokenType::CurlyBracketOpen) == "CurlyBracketOpen");
        REQUIRE(TokenTypeDefiner::getName(TokenType::CurlyBracketClose) == "CurlyBracketClose");
        REQUIRE(TokenTypeDefiner::getName(TokenType::Comma) == "Comma");
        REQUIRE(TokenTypeDefiner::getName(TokenType::Assignment) == "Assignment");
        REQUIRE(TokenTypeDefiner::getName(TokenType::Semicolon) == "Semicolon");

        REQUIRE(TokenTypeDefiner::getName(TokenType::Negation) == "Negation");
        REQUIRE(TokenTypeDefiner::getName(TokenType::Or) == "Or");
        REQUIRE(TokenTypeDefiner::getName(TokenType::And) == "And");
        REQUIRE(TokenTypeDefiner::getName(TokenType::Equality) == "Equality");
        REQUIRE(TokenTypeDefiner::getName(TokenType::Inequality) == "Inequality");
        REQUIRE(TokenTypeDefiner::getName(TokenType::Less) == "Less");
        REQUIRE(TokenTypeDefiner::getName(TokenType::Greater) == "Greater");
        REQUIRE(TokenTypeDefiner::getName(TokenType::LessOrEqual) == "LessOrEqual");
        REQUIRE(TokenTypeDefiner::getName(TokenType::GreaterOrEqual) == "GreaterOrEqual");
        REQUIRE(TokenTypeDefiner::getName(TokenType::Plus) == "Plus");
        REQUIRE(TokenTypeDefiner::getName(TokenType::Minus) == "Minus");
        REQUIRE(TokenTypeDefiner::getName(TokenType::Multiply) == "Multiply");
        REQUIRE(TokenTypeDefiner::getName(TokenType::Divide) == "Divide");
        REQUIRE(TokenTypeDefiner::getName(TokenType::Modulo) == "Modulo");

        REQUIRE(TokenTypeDefiner::getName(TokenType::Identifier) == "Identifier");
        REQUIRE(TokenTypeDefiner::getName(TokenType::NumberLiteral) == "NumberLiteral");
        REQUIRE(TokenTypeDefiner::getName(TokenType::StringLiteral) == "StringLiteral");

        REQUIRE(TokenTypeDefiner::getName(TokenType::Invalid) == "Invalid");
        REQUIRE(TokenTypeDefiner::getName(TokenType::EndOfFile) == "EndOfFile");
    }
}