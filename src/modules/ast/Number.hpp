#ifndef INTERPRETER_NUMBER_HPP
#define INTERPRETER_NUMBER_HPP

#include <ostream>

namespace tkom { namespace ast {

    class Number {
    public:
        explicit Number(const int& value);

        bool operator==(const Number &rhs) const;
        bool operator!=(const Number &rhs) const;

        bool operator<(const Number &rhs) const;
        bool operator>(const Number &rhs) const;
        bool operator<=(const Number &rhs) const;
        bool operator>=(const Number &rhs) const;

        const int& getValue() const;
        void setValue(int value);

        friend std::ostream &operator<<(std::ostream &os, const Number &number);

    private:
        int value;
    };

    inline std::ostream &operator<<(std::ostream &os, const Number &number) {
        os << number.value;
        return os;
    }
}
}

#endif //INTERPRETER_NUMBER_HPP
