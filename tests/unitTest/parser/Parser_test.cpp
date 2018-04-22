#include <catch.hpp>
#include "parser/Parser.hpp"

#include <iostream>
#include "token/TokenType.hpp"
#include "token/Token.hpp"

using namespace tkom;
using namespace tkom::ast;

void accept(const TokenType type, const std::function<void()> ifTrue, const std::function<void()> ifFalse = std::function<void()>()) {
    if(TokenType::If == type) {
        ifTrue();
    } else {
        if (ifFalse) {
            ifFalse();
        } else {
            std::cerr << "ifFalse don't exist\n";
        }
    }
}

class test {
    public:
    explicit test(int a) : a(a){};
    int pa() { return a; };
    int a;
};

SCENARIO("Test for Parser","[Parser]") {
    Token token(TokenType::If);
//    token.value = "value1";
//    std::cerr << token << "\n";
//
//    acceptOrThrow(token.type, [&token](){
//        token.value = "value2";
//    });
//    std::cerr << token << "\n";
//
//    token.value = "value3";
//    auto func = [token](){
//        std::cerr << token << "\n";
//    };
//
//    token.value = "value4";
//    acceptOrThrow(token.type, func);
//    std::cerr << token << "\n";

    test t(2);
    accept(token.type, [&t](){
        std::cerr << t.pa() << "\n";
    });

//    acceptOrThrow(token.type, [t](){
//        std::cerr << t.pa() << "\n";
//    });

    auto fun2 = [p = t.pa()](){
        std::cerr << p << "\n";
    };
    t.a = 3;
    accept(token.type, fun2);
    std::cerr << t.pa() << "\n";
}