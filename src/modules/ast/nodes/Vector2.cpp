#include "Vector2.hpp"

using namespace tkom::ast;


Vector2::Vector2(const int &value1, const int &value2)
        : value({value1, value2}) {
}

bool Vector2::operator==(const Vector2 &rhs) const {
    return value == rhs.value;
}

bool Vector2::operator!=(const Vector2 &rhs) const {
    return !(rhs == *this);
}

bool Vector2::operator<(const Vector2 &rhs) const {
    return value < rhs.value;
}

bool Vector2::operator>(const Vector2 &rhs) const {
    return rhs < *this;
}

bool Vector2::operator<=(const Vector2 &rhs) const {
    return !(rhs < *this);
}

bool Vector2::operator>=(const Vector2 &rhs) const {
    return !(*this < rhs);
}

int &Vector2::operator[](std::size_t idx) {
    return value[idx];
}

const int &Vector2::operator[](std::size_t idx) const {
    return value[idx];
}

const Variable::Type Vector2::getType() const {
    return Type::vector2;
}

const std::vector<int> Vector2::getValue() const {
    return value;
}

const int &Vector2::getValue(const int &index) const {
    return value.at(index);
}

void Vector2::setValue(const std::vector<int> &value) {
    Vector2::value = value;
}
