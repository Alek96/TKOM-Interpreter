#ifndef INTERPRETER_VARIABLE_HPP
#define INTERPRETER_VARIABLE_HPP

#include <memory>
#include <ostream>
#include <vector>

namespace tkom {
    namespace ast {

        class Variable {
        public:
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
    }
}

#endif //INTERPRETER_VARIABLE_HPP

/// jak zrobic variable
/// uproscic i stworzyc jedna klase z vektorem i wszystko stanie sie vektorami

//kiedy rzucac wyjatkami co do matematyki?
//sprawdzac czy mozna / 0 i % 0?
//asercie