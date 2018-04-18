#ifndef INTERPRETER_AST_HPP
#define INTERPRETER_AST_HPP

#include "modules/ast/Return.hpp"

namespace tkom {
    namespace ast {
        class Statement {
        public:
            virtual ~Statement() = default;

            virtual Return run() = 0;
        };
    }
}

#endif //INTERPRETER_AST_HPP