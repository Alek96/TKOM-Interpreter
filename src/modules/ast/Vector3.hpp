#ifndef INTERPRETER_VECTOR3_HPP
#define INTERPRETER_VECTOR3_HPP

#include <vector>
#include <ostream>

namespace tkom { namespace ast {

    class Vector3 {
    public:
        explicit Vector3(const int &value1, const int &value2, const int &value3);

        bool operator==(const Vector3 &rhs) const;
        bool operator!=(const Vector3 &rhs) const;

        bool operator<(const Vector3 &rhs) const;
        bool operator>(const Vector3 &rhs) const;
        bool operator<=(const Vector3 &rhs) const;
        bool operator>=(const Vector3 &rhs) const;

        int& operator[](std::size_t idx);
        const int& operator[](std::size_t idx) const;

        const std::vector<int> getValue() const;
        const int &getValue(const int &index) const;
        void setValue(const std::vector<int> &value);

        friend std::ostream &operator<<(std::ostream &os, const Vector3 &vector3);

    private:
        std::vector<int> value;
    };

    inline std::ostream &operator<<(std::ostream &os, const Vector3 &vector3) {
        os << "(" << vector3.value[0]
           << "," << vector3.value[1]
           << "," << vector3.value[2]
           << ")";
        return os;
    }
}
}

#endif //INTERPRETER_VECTOR3_HPP
