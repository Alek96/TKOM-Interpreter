#ifndef INTERPRETER_TOKENTYPEDEFINER_HPP
#define INTERPRETER_TOKENTYPEDEFINER_HPP

#include <string>
#include "TokenType.hpp"

namespace tkom {

    struct TokenTypeDefiner {
        static const bool exist(const std::string& name);
        static const bool exist(char sign);
        static const TokenType find(const std::string &name);
        static const TokenType find(char sign);
        static const std::string getName(const TokenType& type);

    private:
        static const std::unordered_map<std::string, TokenType>& getKeywords();
        static const std::unordered_map<char, TokenType>& getSimpleSigns();
    };
}

#endif //INTERPRETER_TOKENTYPEDEFINER_HPP
