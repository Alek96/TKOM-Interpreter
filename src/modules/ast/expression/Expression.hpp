#ifndef INTERPRETER_EXPRESSION_HPP
#define INTERPRETER_EXPRESSION_HPP

#include "../Variable.hpp"

namespace tkom { namespace ast {

    class Expression {
    public:
        virtual ~Expression() = default;

        virtual Variable calculate() const = 0;
    };

}}

#endif //INTERPRETER_EXPRESSION_HPP
