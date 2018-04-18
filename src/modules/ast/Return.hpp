#ifndef INTERPRETER_RETURN_HPP
#define INTERPRETER_RETURN_HPP

#include <utility>
#include "ast/Variable.hpp"

namespace tkom {
    namespace ast {

        struct Return {
            enum Type {
                _none,
                _variable,
                _break,
                _continue
            };

            explicit Return(Type type = Type::_none) : type(type) {}

            explicit Return(Type type, Variable variable) : type(type), variable(std::move(variable)) {}

            Type type;
            Variable variable;
        };
    }
}


#endif //INTERPRETER_RETURN_HPP
