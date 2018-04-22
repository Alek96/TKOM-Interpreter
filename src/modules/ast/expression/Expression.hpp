#ifndef INTERPRETER_EXPRESSION_HPP
#define INTERPRETER_EXPRESSION_HPP

#include <list>
#include "../Variable.hpp"

namespace tkom { namespace ast {

    class Expression {
    public:
        virtual ~Expression() = default;

        virtual Variable calculate() const = 0;

        void addPosition(tkom::SignPosition &position) {
            Expression::positions.push_back(position);
        }
    protected:
        std::list<tkom::SignPosition> positions;

    };

}}

#endif //INTERPRETER_EXPRESSION_HPP
