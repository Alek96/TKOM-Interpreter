#ifndef INTERPRETER_VECTOR2_HPP
#define INTERPRETER_VECTOR2_HPP

#include <vector>
#include <ostream>
#include "Variable.hpp"

namespace tkom { namespace ast {

    class Vector2 : public Variable {
    public:
        explicit Vector2(const int &value1, const int &value2);

        bool operator==(const Vector2 &rhs) const;
        bool operator!=(const Vector2 &rhs) const;

        bool operator<(const Vector2 &rhs) const;
        bool operator>(const Vector2 &rhs) const;
        bool operator<=(const Vector2 &rhs) const;
        bool operator>=(const Vector2 &rhs) const;

        int& operator[](std::size_t idx);
        const int& operator[](std::size_t idx) const;

        const Type getType() const override;
        bool compare(const Variable* other) override;

        const std::vector<int> getValue() const;
        const int &getValue(const int &index) const;
        void setValue(const std::vector<int> &value);

        friend std::ostream &operator<<(std::ostream &os, const Vector2 &vector2);

    private:
        std::vector<int> value;
    };

     inline std::ostream &operator<<(std::ostream &os, const Vector2 &vector2){
        os << "(" << vector2.value[0]
           << "," << vector2.value[1]
           << ")";
        return os;
    }
}
}


#endif //INTERPRETER_VECTOR2_HPP
