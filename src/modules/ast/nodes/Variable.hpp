#ifndef INTERPRETER_VARIABLE_HPP
#define INTERPRETER_VARIABLE_HPP

namespace tkom { namespace ast {

    class Variable {
    public:
        enum class Type {
            none,
            number,
            vector2,
            vector3
        };

        virtual const Type getType() const {
            return Type::none;
        }
        virtual bool compare(const Variable* other) {
            return getType() == other->getType();
        }
    };
}
}

#endif //INTERPRETER_VARIABLE_HPP
