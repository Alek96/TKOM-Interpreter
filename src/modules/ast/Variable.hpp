#ifndef INTERPRETER_VARIABLE_HPP
#define INTERPRETER_VARIABLE_HPP

#include <memory>
#include <ostream>
#include "Number.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"

namespace tkom {
    namespace ast {

        class Variable {
        public:
            enum class Type {
                none,
                number,
                vector2,
                vector3
            };

            Variable() = default;
            explicit Variable(std::vector<int> variables);
            Variable(const Variable&) = default;
            Variable(Variable&& rhs) noexcept;
            Variable& operator =(const Variable& rhs) = default;

            int& operator[](int idx);
            const int& operator[](int idx) const;
            std::vector<int>& operator*();

            Variable operator==(const Variable &rhs) const;
            Variable operator!=(const Variable &rhs) const;

            Variable operator<(const Variable &rhs) const;
            Variable operator>(const Variable &rhs) const;
            Variable operator<=(const Variable &rhs) const;
            Variable operator>=(const Variable &rhs) const;

            Variable operator+() const;
            Variable operator-() const;

            Variable operator+(const Variable &rhs) const;
            Variable operator-(const Variable &rhs) const;
            Variable operator*(const Variable &rhs) const;
            Variable operator/(const Variable &rhs) const;
            Variable operator%(const Variable &rhs) const;

            Variable operator!() const;
            Variable operator&&(const Variable &rhs) const;
            Variable operator||(const Variable &rhs) const;

            explicit operator bool() const;

            virtual const Type getType() const;

            friend std::ostream &operator<<(std::ostream &os, const Variable &variable);

        private:
            std::vector<int> variables;

            Variable vTrue() const;
            Variable vFalse() const;
        };


        inline std::ostream &operator<<(std::ostream &os, const Variable &variable) {
            os << "(";
            for (unsigned int i = 0; i < variable.variables.size(); ++i) {
                os << variable.variables[i];
                if(i < variable.variables.size() - 1)
                    os << ",";
            }
            os << ")";
            return os;
        }


        /*class Variable {
        public:
            enum class Type {
                none,
                number,
                vector2,
                vector3
            };
            union variable {
                Number* number = nullptr;
                Vector2* vector2 = nullptr;
                Vector3* vector3 = nullptr;
            };
            explicit Variable(Number* number);
            explicit Variable(Vector2* vector2);
            explicit Variable(Vector3* vector3);

            virtual ~Variable();

            bool operator==(const Variable &rhs) const;

            bool operator!=(const Variable &rhs) const;

            virtual const Type getType() const;

        private:
            const Type type = Type::none;
            variable literal;
        };*/
    }
}

#endif //INTERPRETER_VARIABLE_HPP

/// jak zrobic variable
/// uproscic i stworzyc jedna klase z vektorem i wszystko stanie sie vektorami

//kiedy rzucac wyjatkami co do matematyki?
//sprawdzac czy mozna / 0 i % 0?